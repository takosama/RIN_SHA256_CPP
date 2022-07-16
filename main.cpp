#include<iostream>   
#include <stdlib.h> 
#include <ppl.h>
#include <immintrin.h>
#include <tmmintrin.h>
#include <shaintrin.h>

using namespace std;
using namespace concurrency;
 

alignas(32)  const   uint32_t  K[64]
{
0x428a2f98  ,
0x71374491  ,
0xb5c0fbcf  ,
0xe9b5dba5  ,
0x3956c25b  ,
0x59f111f1  ,
0x923f82a4  ,
0xab1c5ed5  ,
0xd807aa98  ,
0x12835b01  ,
 0x243185be ,
 0x550c7dc3 ,
 0x72be5d74 ,
 0x80deb1fe ,
 0x9bdc06a7 ,
 0xc19bf174 ,
 0xe49b69c1 ,
 0xefbe4786 ,
 0x0fc19dc6 ,
 0x240ca1cc ,
 0x2de92c6f ,
 0x4a7484aa ,
 0x5cb0a9dc ,
 0x76f988da ,
 0x983e5152 ,
 0xa831c66d ,
 0xb00327c8 ,
 0xbf597fc7 ,
 0xc6e00bf3 ,
 0xd5a79147 ,
 0x06ca6351 ,
 0x14292967 ,
 0x27b70a85 ,
 0x2e1b2138 ,
 0x4d2c6dfc ,
 0x53380d13 ,
 0x650a7354 ,
 0x766a0abb ,
 0x81c2c92e ,
 0x92722c85 ,
 0xa2bfe8a1 ,
 0xa81a664b ,
 0xc24b8b70 ,
 0xc76c51a3 ,
 0xd192e819 ,
 0xd6990624 ,
 0xf40e3585 ,
 0x106aa070 ,
 0x19a4c116 ,
 0x1e376c08 ,
 0x2748774c ,
 0x34b0bcb5 ,
 0x391c0cb3 ,
 0x4ed8aa4a ,
 0x5b9cca4f ,
 0x682e6ff3 ,
 0x748f82ee ,
 0x78a5636f ,
 0x84c87814 ,
 0x8cc70208 ,
 0x90befffa ,
 0xa4506ceb ,
 0xbef9a3f7 ,
 0xc67178f2 ,
};

extern "C"  int Compute_NotUseSIMD(int lng, unsigned char* _input, uint32_t * result)
{
    alignas(32)   uint8_t input[64];
    alignas(32)   uint8_t _paded[64];
    alignas(32)   uint32_t W[64];

    uint32_t  a0_ = 0x6a09e667;
    uint32_t  a1_ = 0xbb67ae85;
    uint32_t  a2_ = 0x3c6ef372;
    uint32_t  a3_ = 0xa54ff53a;
    uint32_t  a4_ = 0x510e527f;
    uint32_t  a5_ = 0x9b05688c;
    uint32_t  a6_ = 0x1f83d9ab;
    uint32_t  a7_ = 0x5be0cd19;

    if (lng + 8 >= 64 || lng < 0)
        return -1;
    for (int i = 0; i < 64; i++)
        input[i] = _input[i];

    for (int i = 0; i < 16; i++)
    {
        _paded[0 + 4 * i] = 0;
        _paded[1 + 4 * i] = 0;
        _paded[2 + 4 * i] = 0;
        _paded[3 + 4 * i] = 0;
    }

    for (int i = 0; i < lng; i++)
        _paded[i] = input[i];
    _paded[lng] = 0x80;

    uint32_t size = lng * 8;
    _paded[64 - 4] = (uint8_t)(size >> 24);
    _paded[64 - 3] = (uint8_t)(0xff & (size >> 16));
    _paded[64 - 2] = (uint8_t)(0xff & (size >> 8));
    _paded[64 - 1] = (uint8_t)(0xff & size);

    uint8_t* dest = (uint8_t*)W;
    uint8_t* src = _paded;

    for (int i = 0; i < 2; i++)
    {
        dest[0 + 4 * (i * 8 + 0)] = src[3 + 4 * (i * 8 + 0)];
        dest[1 + 4 * (i * 8 + 0)] = src[2 + 4 * (i * 8 + 0)];
        dest[2 + 4 * (i * 8 + 0)] = src[1 + 4 * (i * 8 + 0)];
        dest[3 + 4 * (i * 8 + 0)] = src[0 + 4 * (i * 8 + 0)];
        dest[0 + 4 * (i * 8 + 1)] = src[3 + 4 * (i * 8 + 1)];
        dest[1 + 4 * (i * 8 + 1)] = src[2 + 4 * (i * 8 + 1)];
        dest[2 + 4 * (i * 8 + 1)] = src[1 + 4 * (i * 8 + 1)];
        dest[3 + 4 * (i * 8 + 1)] = src[0 + 4 * (i * 8 + 1)];
        dest[0 + 4 * (i * 8 + 2)] = src[3 + 4 * (i * 8 + 2)];
        dest[1 + 4 * (i * 8 + 2)] = src[2 + 4 * (i * 8 + 2)];
        dest[2 + 4 * (i * 8 + 2)] = src[1 + 4 * (i * 8 + 2)];
        dest[3 + 4 * (i * 8 + 2)] = src[0 + 4 * (i * 8 + 2)];
        dest[0 + 4 * (i * 8 + 3)] = src[3 + 4 * (i * 8 + 3)];
        dest[1 + 4 * (i * 8 + 3)] = src[2 + 4 * (i * 8 + 3)];
        dest[2 + 4 * (i * 8 + 3)] = src[1 + 4 * (i * 8 + 3)];
        dest[3 + 4 * (i * 8 + 3)] = src[0 + 4 * (i * 8 + 3)];
        dest[0 + 4 * (i * 8 + 4)] = src[3 + 4 * (i * 8 + 4)];
        dest[1 + 4 * (i * 8 + 4)] = src[2 + 4 * (i * 8 + 4)];
        dest[2 + 4 * (i * 8 + 4)] = src[1 + 4 * (i * 8 + 4)];
        dest[3 + 4 * (i * 8 + 4)] = src[0 + 4 * (i * 8 + 4)];
        dest[0 + 4 * (i * 8 + 5)] = src[3 + 4 * (i * 8 + 5)];
        dest[1 + 4 * (i * 8 + 5)] = src[2 + 4 * (i * 8 + 5)];
        dest[2 + 4 * (i * 8 + 5)] = src[1 + 4 * (i * 8 + 5)];
        dest[3 + 4 * (i * 8 + 5)] = src[0 + 4 * (i * 8 + 5)];
        dest[0 + 4 * (i * 8 + 6)] = src[3 + 4 * (i * 8 + 6)];
        dest[1 + 4 * (i * 8 + 6)] = src[2 + 4 * (i * 8 + 6)];
        dest[2 + 4 * (i * 8 + 6)] = src[1 + 4 * (i * 8 + 6)];
        dest[3 + 4 * (i * 8 + 6)] = src[0 + 4 * (i * 8 + 6)];
        dest[0 + 4 * (i * 8 + 7)] = src[3 + 4 * (i * 8 + 7)];
        dest[1 + 4 * (i * 8 + 7)] = src[2 + 4 * (i * 8 + 7)];
        dest[2 + 4 * (i * 8 + 7)] = src[1 + 4 * (i * 8 + 7)];
        dest[3 + 4 * (i * 8 + 7)] = src[0 + 4 * (i * 8 + 7)];
    }

    for (int t = 0; t < 16; t += 4)
    {
        uint32_t t1 = a7_ + (((a4_ >> 6) | (a4_ << (32 - 6))) ^ ((a4_ >> 11) | (a4_ << (32 - 11))) ^ ((a4_ >> 25) | (a4_ << (32 - 25)))) + ((a4_ & a5_) ^ (~a4_ & a6_)) + K[t] + W[t];
        uint32_t t2 = (((a0_ >> 2) | (a0_ << (32 - 2))) ^ ((a0_ >> 13) | (a0_ << (32 - 13))) ^ ((a0_ >> 22) | (a0_ << (32 - 22)))) + ((a0_ & a1_) ^ (a0_ & a2_) ^ (a1_ & a2_));

        uint32_t a3 = a3_ + t1;
        uint32_t  _t1 = a6_ + (((a3 >> 6) | (a3 << (32 - 6))) ^ ((a3 >> 11) | (a3 << (32 - 11))) ^ ((a3 >> 25) | (a3 << (32 - 25)))) + ((a3 & (a4_)) ^ (~a3 & a5_)) + K[t + 1] + W[t + 1];
        uint32_t a0 = t1 + t2;
        uint32_t  _t2 = (((a0 >> 2) | (a0 << (32 - 2))) ^ ((a0 >> 13) | (a0 << (32 - 13))) ^ ((a0 >> 22) | (a0 << (32 - 22)))) + ((a0 & a0_) ^ (a0 & a1_) ^ (a0_ & a1_));

        uint32_t a2 = a2_ + _t1;
        uint32_t  __t1 = a5_ + (((a2 >> 6) | (a2 << (32 - 6))) ^ ((a2 >> 11) | (a2 << (32 - 11))) ^ ((a2 >> 25) | (a2 << (32 - 25)))) + ((a2 & a3) ^ (~a2 & a4_)) + K[t + 2] + W[t + 2];
        uint32_t _a0 = _t1 + _t2;
        uint32_t  __t2 = (((_a0 >> 2) | (_a0 << (32 - 2))) ^ ((_a0 >> 13) | (_a0 << (32 - 13))) ^ ((_a0 >> 22) | (_a0 << (32 - 22)))) + ((_a0 & a0) ^ (_a0 & a0_) ^ (a0 & a0_));

        uint32_t a1 = a1_ + __t1;
        uint32_t  ___t1 = a4_ + (((a1 >> 6) | (a1 << (32 - 6))) ^ ((a1 >> 11) | (a1 << (32 - 11))) ^ ((a1 >> 25) | (a1 << (32 - 25)))) + ((a1 & a2) ^ (~a1 & a3)) + K[t + 3] + W[t + 3];
        uint32_t __a0 = __t1 + __t2;
        uint32_t  ___t2 = (((__a0 >> 2) | (__a0 << (32 - 2))) ^ ((__a0 >> 13) | (__a0 << (32 - 13))) ^ ((__a0 >> 22) | (__a0 << (32 - 22)))) + ((__a0 & _a0) ^ (__a0 & a0) ^ (_a0 & a0));

        a7_ = a3_ + t1;
        a6_ = a2_ + _t1;
        a5_ = a1_ + __t1;
        a4_ = a0_ + ___t1;
        a3_ = t1 + t2;
        a2_ = _t1 + _t2;
        a1_ = __t1 + __t2;
        a0_ = ___t1 + ___t2;
    }

    for (int t = 16; t < 64; t += 4)
    {
        uint32_t x0 = W[t - 2];
        uint32_t x1 = W[t - 15];
        W[t] = (((x1 >> 7) | (x1 << (32 - 7))) ^ ((x1 >> 18) | (x1 << (32 - 18))) ^ (x1 >> 3)) + (((x0 >> 17) | (x0 << (32 - 17))) ^ ((x0 >> 19) | (x0 << (32 - 19))) ^ (x0 >> 10)) + W[t - 16] + W[t - 7];
        uint32_t t1 = a7_ + (((a4_ >> 6) | (a4_ << (32 - 6))) ^ ((a4_ >> 11) | (a4_ << (32 - 11))) ^ ((a4_ >> 25) | (a4_ << (32 - 25)))) + ((a4_ & a5_) ^ (~a4_ & a6_)) + K[t] + W[t];
        uint32_t t2 = (((a0_ >> 2) | (a0_ << (32 - 2))) ^ ((a0_ >> 13) | (a0_ << (32 - 13))) ^ ((a0_ >> 22) | (a0_ << (32 - 22)))) + ((a0_ & a1_) ^ (a0_ & a2_) ^ (a1_ & a2_));

        x0 = W[t - 1];
        x1 = W[t - 14];
        W[t + 1] = (((x1 >> 7) | (x1 << (32 - 7))) ^ ((x1 >> 18) | (x1 << (32 - 18))) ^ (x1 >> 3)) + (((x0 >> 17) | (x0 << (32 - 17))) ^ ((x0 >> 19) | (x0 << (32 - 19))) ^ (x0 >> 10)) + W[t - 15] + W[t - 6];
        uint32_t a3 = a3_ + t1;
        uint32_t  _t1 = a6_ + (((a3 >> 6) | (a3 << (32 - 6))) ^ ((a3 >> 11) | (a3 << (32 - 11))) ^ ((a3 >> 25) | (a3 << (32 - 25)))) + ((a3 & (a4_)) ^ (~a3 & a5_)) + K[t + 1] + W[t + 1];
        uint32_t a0 = t1 + t2;
        uint32_t  _t2 = (((a0 >> 2) | (a0 << (32 - 2))) ^ ((a0 >> 13) | (a0 << (32 - 13))) ^ ((a0 >> 22) | (a0 << (32 - 22)))) + ((a0 & a0_) ^ (a0 & a1_) ^ (a0_ & a1_));

        x0 = W[t];
        x1 = W[t - 13];
        W[t + 2] = (((x1 >> 7) | (x1 << (32 - 7))) ^ ((x1 >> 18) | (x1 << (32 - 18))) ^ (x1 >> 3)) + (((x0 >> 17) | (x0 << (32 - 17))) ^ ((x0 >> 19) | (x0 << (32 - 19))) ^ (x0 >> 10)) + W[t - 14] + W[t - 5];
        uint32_t a2 = a2_ + _t1;
        uint32_t  __t1 = a5_ + (((a2 >> 6) | (a2 << (32 - 6))) ^ ((a2 >> 11) | (a2 << (32 - 11))) ^ ((a2 >> 25) | (a2 << (32 - 25)))) + ((a2 & a3) ^ (~a2 & a4_)) + K[t + 2] + W[t + 2];
        uint32_t _a0 = _t1 + _t2;
        uint32_t  __t2 = (((_a0 >> 2) | (_a0 << (32 - 2))) ^ ((_a0 >> 13) | (_a0 << (32 - 13))) ^ ((_a0 >> 22) | (_a0 << (32 - 22)))) + ((_a0 & a0) ^ (_a0 & a0_) ^ (a0 & a0_));

        x0 = W[t + 1];
        x1 = W[t - 12];
        W[t + 3] = (((x1 >> 7) | (x1 << (32 - 7))) ^ ((x1 >> 18) | (x1 << (32 - 18))) ^ (x1 >> 3)) + (((x0 >> 17) | (x0 << (32 - 17))) ^ ((x0 >> 19) | (x0 << (32 - 19))) ^ (x0 >> 10)) + W[t - 13] + W[t - 4];
        uint32_t a1 = a1_ + __t1;
        uint32_t  ___t1 = a4_ + (((a1 >> 6) | (a1 << (32 - 6))) ^ ((a1 >> 11) | (a1 << (32 - 11))) ^ ((a1 >> 25) | (a1 << (32 - 25)))) + ((a1 & a2) ^ (~a1 & a3)) + K[t + 3] + W[t + 3];
        uint32_t __a0 = __t1 + __t2;
        uint32_t  ___t2 = (((__a0 >> 2) | (__a0 << (32 - 2))) ^ ((__a0 >> 13) | (__a0 << (32 - 13))) ^ ((__a0 >> 22) | (__a0 << (32 - 22)))) + ((__a0 & _a0) ^ (__a0 & a0) ^ (_a0 & a0));

        a7_ = a3_ + t1;
        a6_ = a2_ + _t1;
        a5_ = a1_ + __t1;
        a4_ = a0_ + ___t1;
        a3_ = t1 + t2;
        a2_ = _t1 + _t2;
        a1_ = __t1 + __t2;
        a0_ = ___t1 + ___t2;
    }

    result[0] = a0_ + 0x6a09e667;
    result[1] = a1_ + 0xbb67ae85;
    result[2] = a2_ + 0x3c6ef372;
    result[3] = a3_ + 0xa54ff53a;
    result[4] = a4_ + 0x510e527f;
    result[5] = a5_ + 0x9b05688c;
    result[6] = a6_ + 0x1f83d9ab;
    result[7] = a7_ + 0x5be0cd19;
        return a0_;
}

union __K {
    unsigned __int32 dw[64];
    __m128i x[16];
};

extern "C" __attribute__((__target__("sha"))) int  Compute_UseSIMD(int lng, unsigned char* _input, uint32_t* result)
{
    auto _i = _mm_set_epi8(12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3);
    auto _ms = _mm256_setr_epi32(3, 2, 7, 6, 1, 0, 5, 4);
    __m128i p;

    union __K _K =
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };

    uint8_t input[64];

    uint32_t  a0_ = 0x6a09e667;
    uint32_t  a1_ = 0xbb67ae85;
    uint32_t  a2_ = 0x3c6ef372;
    uint32_t  a3_ = 0xa54ff53a;
    uint32_t  a4_ = 0x510e527f;
    uint32_t  a5_ = 0x9b05688c;
    uint32_t  a6_ = 0x1f83d9ab;
    uint32_t  a7_ = 0x5be0cd19;

    if (lng + 8 >= 64 || lng < 0)
        return -1;

    for (int i = 0; i < 64; i++)
        input[i] = 0;

    for (int i = 0; i < lng; i++)
        input[i] = _input[i];
    input[lng] = 0x80;

    uint32_t size = lng * 8;
    input[64 - 4] = (uint8_t)(size >> 24);
    input[64 - 3] = (uint8_t)(0xff & (size >> 16));
    input[64 - 2] = (uint8_t)(0xff & (size >> 8));
    input[64 - 1] = (uint8_t)(0xff & size);

    auto msg = (const __m128i*)input;
    auto  p0 = _mm_shuffle_epi8(_mm_loadu_si128(msg + 0), _i);
    auto  p1 = _mm_shuffle_epi8(_mm_loadu_si128(msg + 1), _i);
    auto  p2 = _mm_shuffle_epi8(_mm_loadu_si128(msg + 2), _i);
    auto  p3 = _mm_shuffle_epi8(_mm_loadu_si128(msg + 3), _i);

    auto v0 = _mm_set_epi32(a0_, a1_, a4_, a5_);
    auto v1 = _mm_set_epi32(a2_, a3_, a6_, a7_);
    auto _p1 = _mm_set_epi32(a0_, a1_, a4_, a5_);
    auto _p2 = _mm_set_epi32(a2_, a3_, a6_, a7_);


    p = _mm_add_epi32(p0, _K.x[0]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p = _mm_add_epi32(p1, _K.x[1]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p = _mm_add_epi32(p2, _K.x[2]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p = _mm_add_epi32(p3, _K.x[3]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);


    p0 = _mm_sha256msg1_epu32(p0, p1);
    p0 = _mm_add_epi32(p0, _mm_alignr_epi8(p3, p2, 4));
    p0 = _mm_sha256msg2_epu32(p0, p3);
    p = _mm_add_epi32(p0, _K.x[4]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p1 = _mm_sha256msg1_epu32(p1, p2);
    p1 = _mm_add_epi32(p1, _mm_alignr_epi8(p0, p3, 4));
    p1 = _mm_sha256msg2_epu32(p1, p0);
    p = _mm_add_epi32(p1, _K.x[5]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p2 = _mm_sha256msg1_epu32(p2, p3);
    p2 = _mm_add_epi32(p2, _mm_alignr_epi8(p1, p0, 4));
    p2 = _mm_sha256msg2_epu32(p2, p1);
    p = _mm_add_epi32(p2, _K.x[6]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p3 = _mm_sha256msg1_epu32(p3, p0);
    p3 = _mm_add_epi32(p3, _mm_alignr_epi8(p2, p1, 4));
    p3 = _mm_sha256msg2_epu32(p3, p2);
    p = _mm_add_epi32(p3, _K.x[7]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);


    p0 = _mm_sha256msg1_epu32(p0, p1);
    p0 = _mm_add_epi32(p0, _mm_alignr_epi8(p3, p2, 4));
    p0 = _mm_sha256msg2_epu32(p0, p3);
    p = _mm_add_epi32(p0, _K.x[8]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p1 = _mm_sha256msg1_epu32(p1, p2);
    p1 = _mm_add_epi32(p1, _mm_alignr_epi8(p0, p3, 4));
    p1 = _mm_sha256msg2_epu32(p1, p0);
    p = _mm_add_epi32(p1, _K.x[9]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p2 = _mm_sha256msg1_epu32(p2, p3);
    p2 = _mm_add_epi32(p2, _mm_alignr_epi8(p1, p0, 4));
    p2 = _mm_sha256msg2_epu32(p2, p1);
    p = _mm_add_epi32(p2, _K.x[10]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p3 = _mm_sha256msg1_epu32(p3, p0);
    p3 = _mm_add_epi32(p3, _mm_alignr_epi8(p2, p1, 4));
    p3 = _mm_sha256msg2_epu32(p3, p2);
    p = _mm_add_epi32(p3, _K.x[11]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);


    p0 = _mm_sha256msg1_epu32(p0, p1);
    p0 = _mm_add_epi32(p0, _mm_alignr_epi8(p3, p2, 4));
    p0 = _mm_sha256msg2_epu32(p0, p3);
    p = _mm_add_epi32(p0, _K.x[12]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p1 = _mm_sha256msg1_epu32(p1, p2);
    p1 = _mm_add_epi32(p1, _mm_alignr_epi8(p0, p3, 4));
    p1 = _mm_sha256msg2_epu32(p1, p0);
    p = _mm_add_epi32(p1, _K.x[13]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p2 = _mm_sha256msg1_epu32(p2, p3);
    p2 = _mm_add_epi32(p2, _mm_alignr_epi8(p1, p0, 4));
    p2 = _mm_sha256msg2_epu32(p2, p1);
    p = _mm_add_epi32(p2, _K.x[14]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    p3 = _mm_sha256msg1_epu32(p3, p0);
    p3 = _mm_add_epi32(p3, _mm_alignr_epi8(p2, p1, 4));
    p3 = _mm_sha256msg2_epu32(p3, p2);
    p = _mm_add_epi32(p3, _K.x[15]);
    _p2 = _mm_sha256rnds2_epu32(_p2, _p1, p);
    p = _mm_unpackhi_epi64(p, p);
    _p1 = _mm_sha256rnds2_epu32(_p1, _p2, p);

    _mm_store_si128((__m128i*)result, _mm_add_epi32(_p1, v0));
    _mm_store_si128((__m128i*)(result + 4), _mm_add_epi32(_p2, v1));
    auto y = _mm256_loadu_si256((__m256i*)result);
    auto ym = _mm256_permutevar8x32_epi32(y, _ms);
    _mm256_storeu_si256((__m256i*)result, ym);

    return result[0];
}

long long int   cnt[16];

int test()
{
    parallel_for(0, 16, [&](size_t i) {
        uint8_t* input = new uint8_t[8]
        {
            114,105,110,116,121,97,33,33
        };
        uint32_t ans = 0;

         uint32_t* result = new uint32_t[8];
        while (true)
        {
            auto rtn = Compute_UseSIMD(8,input, result);
            input[0]++;
            ans += rtn;
            cnt[i]++;
        }
        });
     
    return 0;
 //   return rtn;
}

int main(void)
{
    std::thread th_a(test);
    char t[100];
    

    while (true)
    {
        _sleep(1000);
        int sum = 0;
        for (int i = 0; i < 16; i++)
        {
            sum += cnt[i];
            cnt[i] = 0;
        }

        printf("%d\n", sum);
    }
    th_a.join();
}

