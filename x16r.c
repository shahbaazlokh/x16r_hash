#include "x16r.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "sha3/sph_blake.h"
#include "sha3/sph_bmw.h"
#include "sha3/sph_groestl.h"
#include "sha3/sph_jh.h"
#include "sha3/sph_keccak.h"
#include "sha3/sph_skein.h"
#include "sha3/sph_luffa.h"
#include "sha3/sph_cubehash.h"
#include "sha3/sph_shavite.h"
#include "sha3/sph_simd.h"
#include "sha3/sph_echo.h"
#include "sha3/sph_hamsi.h"
#include "sha3/sph_fugue.h"
#include "sha3/sph_shabal.h"
#include "sha3/sph_whirlpool.h"
#include "sha3/sph_sha2.h"

enum Algo {
    BLAKE = 0,
    BMW,
    GROESTL,
    JH,
    KECCAK,
    SKEIN,
    LUFFA,
    CUBEHASH,
    SHAVITE,
    SIMD,
    ECHO,
    HAMSI,
    FUGUE,
    SHABAL,
    WHIRLPOOL,
    SHA512,
    HASH_FUNC_COUNT
};

static void getAlgoString(const uint8_t* prevblock, char *output)
{
    char *sptr = output;
    printf("Hash Sequence:");
    for (int j = 0; j < HASH_FUNC_COUNT; j++) {
        char b = (15 - j) >> 1; // 16 ascii hex chars, reversed
        uint8_t algoDigit = (j & 1) ? prevblock[b] & 0xF : prevblock[b] >> 4;
        if (algoDigit >= 10)
            sprintf(sptr, "%c", 'A' + (algoDigit - 10));
        else
            sprintf(sptr, "%u", (uint32_t) algoDigit);
	printf("%02x",prevblock[b]);
        sptr++;
    }
    *sptr = '\0'; 
    printf("\r\n");
}

void x16r_hash(const char* input, char* output)
{
    uint32_t hash[64/4];
    char hashOrder[HASH_FUNC_COUNT + 1] = { 0 };

    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    sph_hamsi512_context     ctx_hamsi;
    sph_fugue512_context     ctx_fugue;
    sph_shabal512_context    ctx_shabal;
    sph_whirlpool_context    ctx_whirlpool;
    sph_sha512_context       ctx_sha512;

    void *in = (void*) input;
    int size = 80;

    getAlgoString(&input[4], hashOrder);
    uint8_t hashb[32];

    for (int i = 0; i < 16; i++) {
        const char elem = hashOrder[i];
        const uint8_t algo = elem >= 'A' ? elem - 'A' + 10 : elem - '0';
	printf("algo = %d", algo);
	printf("\r\n");
        switch (algo) {
            case BLAKE:
            sph_blake512_init(&ctx_blake);
            sph_blake512(&ctx_blake, in, size);
            sph_blake512_close(&ctx_blake, hash);
	    memcpy(hashb, hash, 32);
	    printf("Blake hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case BMW:
            sph_bmw512_init(&ctx_bmw);
            sph_bmw512(&ctx_bmw, in, size);
            sph_bmw512_close(&ctx_bmw, hash);
	    memcpy(hashb, hash, 32);
	    printf("Bmw hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");

            break;
            case GROESTL:
            sph_groestl512_init(&ctx_groestl);
            sph_groestl512(&ctx_groestl, in, size);
            sph_groestl512_close(&ctx_groestl, hash);
            memcpy(hashb, hash, 32);
	    printf("grostel hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");

	    break;
            case SKEIN:
            sph_skein512_init(&ctx_skein);
            sph_skein512(&ctx_skein, in, size);
            sph_skein512_close(&ctx_skein, hash);
	    memcpy(hashb, hash, 32);
	    printf("skein hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");

            break;
            case JH:
            sph_jh512_init(&ctx_jh);
            sph_jh512(&ctx_jh, in, size);
            sph_jh512_close(&ctx_jh, hash);
	    memcpy(hashb, hash, 32);
	    printf("jh hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case KECCAK:
            sph_keccak512_init(&ctx_keccak);
            sph_keccak512(&ctx_keccak, in, size);
            sph_keccak512_close(&ctx_keccak, hash);
	    memcpy(hashb, hash, 32);
	    printf("keccak hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case LUFFA:
            sph_luffa512_init(&ctx_luffa);
            sph_luffa512(&ctx_luffa, in, size);
            sph_luffa512_close(&ctx_luffa, hash);
	    memcpy(hashb, hash, 32);
	    printf("luffa hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case CUBEHASH:
            sph_cubehash512_init(&ctx_cubehash);
            sph_cubehash512(&ctx_cubehash, in, size);
            sph_cubehash512_close(&ctx_cubehash, hash);
	    memcpy(hashb, hash, 32);
	    printf("cubehash hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case SHAVITE:
            sph_shavite512_init(&ctx_shavite);
            sph_shavite512(&ctx_shavite, in, size);
            sph_shavite512_close(&ctx_shavite, hash);
	    memcpy(hashb, hash, 32);
	    printf("shavite hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case SIMD:
            sph_simd512_init(&ctx_simd);
            sph_simd512(&ctx_simd, in, size);
            sph_simd512_close(&ctx_simd, hash);
	    memcpy(hashb, hash, 32);
	    printf("simd hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case ECHO:
            sph_echo512_init(&ctx_echo);
            sph_echo512(&ctx_echo, in, size);
            sph_echo512_close(&ctx_echo, hash);
	    memcpy(hashb, hash, 32);
	    printf("echo hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case HAMSI:
            sph_hamsi512_init(&ctx_hamsi);
            sph_hamsi512(&ctx_hamsi, in, size);
            sph_hamsi512_close(&ctx_hamsi, hash);
	    memcpy(hashb, hash, 32);
	    printf("hamsi hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case FUGUE:
            sph_fugue512_init(&ctx_fugue);
            sph_fugue512(&ctx_fugue, in, size);
            sph_fugue512_close(&ctx_fugue, hash);
	    memcpy(hashb, hash, 32);
	    printf("fugue hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case SHABAL:
            sph_shabal512_init(&ctx_shabal);
            sph_shabal512(&ctx_shabal, in, size);
            sph_shabal512_close(&ctx_shabal, hash);
	    memcpy(hashb, hash, 32);
	    printf("shabal hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case WHIRLPOOL:
            sph_whirlpool_init(&ctx_whirlpool);
            sph_whirlpool(&ctx_whirlpool, in, size);
            sph_whirlpool_close(&ctx_whirlpool, hash);
	    memcpy(hashb, hash, 32);
	    printf("whirlpool hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
            case SHA512:
            sph_sha512_init(&ctx_sha512);
            sph_sha512(&ctx_sha512,(const void*) in, size);
            sph_sha512_close(&ctx_sha512,(void*) hash);
	    memcpy(hashb, hash, 32);
	    printf("sha512 hash = ");
            for(int i = 0; i<32 ; i++){
		printf("%02x", hashb[i]);
             }
	    printf("\r\n");
            break;
        }
        in = (void*) hash;
        size = 64;
    }
    memcpy(output, hash, 32);
}
