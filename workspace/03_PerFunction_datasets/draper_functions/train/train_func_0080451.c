facos(_MIPD_ flash x,flash y)
{
    int op[5];
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(62)

    fasin(_MIPP_ x,y);
    fpi(_MIPP_ mr_mip->pi);
    op[0]=0x6C;
    op[1]=(-2);
    op[2]=1;
    op[3]=2;
    op[4]=0;
    flop(_MIPP_ y,mr_mip->pi,op,y);
    MR_OUT
}
