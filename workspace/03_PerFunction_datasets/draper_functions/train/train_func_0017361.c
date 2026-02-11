epoint2_negate(_MIPD_ epoint *p)
{
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (p->marker==MR_EPOINT_INFINITY) return;
    MR_IN(130)
#ifndef MR_AFFINE_ONLY
    if (p->marker==MR_EPOINT_GENERAL)
    {
#ifndef MR_NO_SS
        if (mr_mip->SS)
        {
             add2(p->Y,p->Z,p->Y);
        }
        else
        {
#endif
            modmult2(_MIPP_ p->X,p->Z,mr_mip->w1);
            add2(p->Y,mr_mip->w1,p->Y);
#ifndef MR_NO_SS
        }
#endif
    }
    else
    {
#endif
#ifndef MR_NO_SS
        if (mr_mip->SS)  incr2(p->Y,1,p->Y);
        else
#endif
            add2(p->Y,p->X,p->Y);
#ifndef MR_AFFINE_ONLY
    }
#endif
    MR_OUT
}
