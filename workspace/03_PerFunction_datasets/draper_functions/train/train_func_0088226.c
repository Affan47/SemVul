zzn2_negate(_MIPD_ zzn2 *x,zzn2 *w)
{
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    MR_IN(157)
    zzn2_copy(x,w);
    nres_negate(_MIPP_ w->a,w->a);
    nres_negate(_MIPP_ w->b,w->b);
    MR_OUT
}
