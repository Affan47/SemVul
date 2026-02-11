irand(_MIPD_ mr_unsign32 seed)
{
    int i,in;
    mr_unsign32 t,m=1L;
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    mr_mip->borrow=0L;
    mr_mip->rndptr=0;
    mr_mip->ira[0]=seed;
    for (i=1;i<NK;i++)
    {
        in=(NV*i)%NK;
        mr_mip->ira[in]=m;
        t=m;
        m=seed-m;
        seed=t;
    }
    for (i=0;i<1000;i++) brand(_MIPPO_ );
}
