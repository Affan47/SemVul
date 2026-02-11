Skein_256_Final(Skein_256_Ctxt_t *ctx, u08b_t *hashVal)
    {
    size_t i,n,byteCnt;
    u64b_t X[SKEIN_256_STATE_WORDS];
    Skein_Assert(ctx->h.bCnt <= SKEIN_256_BLOCK_BYTES,SKEIN_FAIL);

    ctx->h.T[1] |= SKEIN_T1_FLAG_FINAL;
    if (ctx->h.bCnt < SKEIN_256_BLOCK_BYTES)
        memset(&ctx->b[ctx->h.bCnt],0,SKEIN_256_BLOCK_BYTES - ctx->h.bCnt);

    Skein_256_Process_Block(ctx,ctx->b,1,ctx->h.bCnt);


    byteCnt = (ctx->h.hashBitLen + 7) >> 3;


    memset(ctx->b,0,sizeof(ctx->b));
    memcpy(X,ctx->X,sizeof(X));
    for (i=0;i < byteCnt;i += SKEIN_256_BLOCK_BYTES)
        {
        ((u64b_t *)ctx->b)[0]= Skein_Swap64((u64b_t) i);
        Skein_Start_New_Type(ctx,OUT_FINAL);
        Skein_256_Process_Block(ctx,ctx->b,1,sizeof(u64b_t));
        n = byteCnt - i;
        if (n >= SKEIN_256_BLOCK_BYTES)
            n  = SKEIN_256_BLOCK_BYTES;
        Skein_Put64_LSB_First(hashVal+i,ctx->X,n);
        Skein_Show_Final(256,&ctx->h,n,hashVal+i*SKEIN_256_BLOCK_BYTES);
        memcpy(ctx->X,X,sizeof(X));
        }
    return SKEIN_SUCCESS;
    }
