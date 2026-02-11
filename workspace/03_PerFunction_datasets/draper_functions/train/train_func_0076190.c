pdf_gen_xor(pdf_ctx *pc, UINT8 nonce[8], UINT8 buf[8])
{


#if (UMAC_OUTPUT_LEN == 4)
#define LOW_BIT_MASK 3
#elif (UMAC_OUTPUT_LEN == 8)
#define LOW_BIT_MASK 1
#elif (UMAC_OUTPUT_LEN > 8)
#define LOW_BIT_MASK 0
#endif

    UINT8 tmp_nonce_lo[4];
    int index = nonce[7] & LOW_BIT_MASK;
    *(UINT32 *)tmp_nonce_lo = ((UINT32 *)nonce)[1];
    tmp_nonce_lo[3] &= ~LOW_BIT_MASK;

    if ( (((UINT32 *)tmp_nonce_lo)[0] != ((UINT32 *)pc->nonce)[1]) ||
         (((UINT32 *)nonce)[0] != ((UINT32 *)pc->nonce)[0]) )
    {
        ((UINT32 *)pc->nonce)[0] = ((UINT32 *)nonce)[0];
        ((UINT32 *)pc->nonce)[1] = ((UINT32 *)tmp_nonce_lo)[0];
        aes_encryption(pc->nonce, pc->cache, pc->prf_key);
    }

#if (UMAC_OUTPUT_LEN == 4)
    *((UINT32 *)buf) ^= ((UINT32 *)pc->cache)[index];
#elif (UMAC_OUTPUT_LEN == 8)
    *((UINT64 *)buf) ^= ((UINT64 *)pc->cache)[index];
#elif (UMAC_OUTPUT_LEN == 12)
    ((UINT64 *)buf)[0] ^= ((UINT64 *)pc->cache)[0];
    ((UINT32 *)buf)[2] ^= ((UINT32 *)pc->cache)[2];
#elif (UMAC_OUTPUT_LEN == 16)
    ((UINT64 *)buf)[0] ^= ((UINT64 *)pc->cache)[0];
    ((UINT64 *)buf)[1] ^= ((UINT64 *)pc->cache)[1];
#endif
}
