bigrand(_MIPD_ big w,big x)
{
    int m;
    mr_small r;
#ifdef MR_FP
    mr_small dres;
#endif
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(20)


    m=0;
    zero(mr_mip->w0);

    do
    {
        m++;
        mr_mip->w0->len=m;
        r=brand(_MIPPO_ );
        if (mr_mip->base==0) mr_mip->w0->w[m-1]=r;
        else                 mr_mip->w0->w[m-1]=MR_REMAIN(r,mr_mip->base);
    } while (mr_compare(mr_mip->w0,w)<0);
    mr_lzero(mr_mip->w0);
    divide(_MIPP_ mr_mip->w0,w,w);

    copy(mr_mip->w0,x);


    MR_OUT
}
