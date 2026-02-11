intelaes_multikey_encrypt(int size)
{
    aes_context     *acpa[4];
    u_int64_t       *bfp = (u_int64_t *)bufb;


    while(size >= (4*512)) {
        acpa[0] = multiKeyCtx[((unsigned)devSect0    ) & 0x3F];
        acpa[1] = multiKeyCtx[((unsigned)devSect0 + 1) & 0x3F];
        acpa[2] = multiKeyCtx[((unsigned)devSect0 + 2) & 0x3F];
        acpa[3] = multiKeyCtx[((unsigned)devSect0 + 3) & 0x3F];
        memcpy(&ivbuf[0], &partialMD5[0], 16);
        memcpy(&ivbuf[2], &partialMD5[0], 16);
        memcpy(&ivbuf[4], &partialMD5[0], 16);
        memcpy(&ivbuf[6], &partialMD5[0], 16);
#if defined(HAVE_MD5_2X_IMPLEMENTATION)

        compute_md5_iv_v3_2x((u_int32_t *)(&ivbuf[0]), (u_int32_t *)(bfp + 0x02));
        compute_md5_iv_v3_2x((u_int32_t *)(&ivbuf[4]), (u_int32_t *)(bfp + 0x82));
#else
        compute_md5_iv_v3((u_int32_t *)(&ivbuf[0]), (u_int32_t *)(bfp + 0x02));
        compute_md5_iv_v3((u_int32_t *)(&ivbuf[2]), (u_int32_t *)(bfp + 0x42));
        compute_md5_iv_v3((u_int32_t *)(&ivbuf[4]), (u_int32_t *)(bfp + 0x82));
        compute_md5_iv_v3((u_int32_t *)(&ivbuf[6]), (u_int32_t *)(bfp + 0xC2));
#endif
        intel_aes_cbc_enc_4x512(&acpa[0], bfp, bfp, ivbuf);
        size -= 4*512;
        bfp += 4*64;
    }

    while(size > 0) {
        acpa[0] = multiKeyCtx[((unsigned)devSect0) & 0x3F];
        memcpy(ivbuf, &partialMD5[0], 16);
        compute_md5_iv_v3((u_int32_t *)ivbuf, (u_int32_t *)(bfp + 2));
        intel_aes_cbc_encrypt(acpa[0], bfp, bfp, 512, ivbuf);
        size -= 512;
        bfp += 64;
    }
}
