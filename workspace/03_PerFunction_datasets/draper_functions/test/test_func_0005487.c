ecurve_init(_MIPD_ big a,big b,big p,int type)
{


    int as;
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(93)

#ifndef MR_NO_SS
    mr_mip->SS=FALSE;
#endif

    prepare_monty(_MIPP_ p);

    mr_mip->Asize=size(a);
    if (mr_abs(mr_mip->Asize)==MR_TOOBIG)
    {
        if (mr_mip->Asize>=0)
        {
           copy(a,mr_mip->w1);
           divide(_MIPP_ mr_mip->w1,p,p);
           subtract(_MIPP_ p,mr_mip->w1,mr_mip->w1);
           as=size(mr_mip->w1);
           if (as<MR_TOOBIG) mr_mip->Asize=-as;
        }
    }
    nres(_MIPP_ a,mr_mip->A);

    mr_mip->Bsize=size(b);
    if (mr_abs(mr_mip->Bsize)==MR_TOOBIG)
    {
        if (mr_mip->Bsize>=0)
        {
           copy(b,mr_mip->w1);
           divide(_MIPP_ mr_mip->w1,p,p);
           subtract(_MIPP_ p,mr_mip->w1,mr_mip->w1);
           as=size(mr_mip->w1);
           if (as<MR_TOOBIG) mr_mip->Bsize=-as;
        }
    }

    nres(_MIPP_ b,mr_mip->B);
#ifdef MR_EDWARDS
    mr_mip->coord=MR_PROJECTIVE;
#else
#ifndef MR_AFFINE_ONLY
    if (type==MR_BEST) mr_mip->coord=MR_PROJECTIVE;
    else mr_mip->coord=type;
#else
    if (type==MR_PROJECTIVE)
        mr_berror(_MIPP_ MR_ERR_NOT_SUPPORTED);
#endif
#endif
    MR_OUT
    return;
}
