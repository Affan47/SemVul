ecurve2_init(_MIPD_ int m,int a,int b,int c,big a2,big a6,BOOL check,int type)
{
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif


    if (mr_mip->ERNUM) return FALSE;

#ifndef MR_NOKOBLITZ
    mr_mip->KOBLITZ=FALSE;
#endif

#ifndef MR_NO_SS
    mr_mip->SS=FALSE;
    if (m<0)
    {
        mr_mip->SS=TRUE;

        m=-m;
        if (size(a2)!=1) return FALSE;
        if (size(a6) >1) return FALSE;
    }
#else
    if (m<0) return FALSE;
#endif
    if (size(a2)<0) return FALSE;
    if (size(a6)<0) return FALSE;
    MR_IN(123)

    if (!prepare_basis(_MIPP_ m,a,b,c,check))
    {
        MR_OUT
        return FALSE;
    }

    mr_mip->Asize=size(a2);
    mr_mip->Bsize=size(a6);

#ifndef MR_NOKOBLITZ
#ifndef MR_NO_SS
    if (!mr_mip->SS && mr_mip->Bsize==1)
#else
    if (mr_mip->Bsize==1)
#endif
    {
        if (mr_mip->Asize==0 || mr_mip->Asize==1)
        {
            mr_mip->KOBLITZ=TRUE;
        }
    }
#endif

	if (mr_mip->Asize==MR_TOOBIG)
        copy(a2,mr_mip->A);

    if (mr_mip->Bsize==MR_TOOBIG)
        copy(a6,mr_mip->B);

#ifndef MR_AFFINE_ONLY
    if (type==MR_BEST) mr_mip->coord=MR_PROJECTIVE;
    else mr_mip->coord=type;
#else
    if (type==MR_PROJECTIVE)
        mr_berror(_MIPP_ MR_ERR_NOT_SUPPORTED);
#endif
    MR_OUT
    return TRUE;
}
