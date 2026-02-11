brand(_MIPDO_ )
{
    int i,k;
    mr_unsign32 pdiff,t;
    mr_small r;
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->lg2b>32)
    {
        mr_mip->rndptr+=2;
        if (mr_mip->rndptr<NK-1)
        {
            r=(mr_small)mr_mip->ira[mr_mip->rndptr];
            r=mr_shiftbits(r,mr_mip->lg2b-32);
            r+=(mr_small)mr_mip->ira[mr_mip->rndptr+1];
            return r;
        }
    }
    else
    {
        mr_mip->rndptr++;
        if (mr_mip->rndptr<NK) return (mr_small)mr_mip->ira[mr_mip->rndptr];
    }
    mr_mip->rndptr=0;
    for (i=0,k=NK-NJ;i<NK;i++,k++)
    {
        if (k==NK) k=0;
        t=mr_mip->ira[k];
        pdiff=t - mr_mip->ira[i] - mr_mip->borrow;
        if (pdiff<t) mr_mip->borrow=0;
        if (pdiff>t) mr_mip->borrow=1;
        mr_mip->ira[i]=pdiff;
    }
    if (mr_mip->lg2b>32)
    {
        r=(mr_small)mr_mip->ira[0];
        r=mr_shiftbits(r,mr_mip->lg2b-32);
        r+=(mr_small)mr_mip->ira[1];
        return r;
    }
    else return (mr_small)(mr_mip->ira[0]);
}
