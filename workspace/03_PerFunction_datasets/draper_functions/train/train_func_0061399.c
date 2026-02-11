zzn3_imul(_MIPD_ zzn3 *x,int y,zzn3 *w)
{
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    MR_IN(185)
    if (size(x->a)!=0) nres_premult(_MIPP_ x->a,y,w->a);
    else zero(w->a);
    if (size(x->b)!=0) nres_premult(_MIPP_ x->b,y,w->b);
    else zero(w->b);
    if (size(x->c)!=0) nres_premult(_MIPP_ x->c,y,w->c);
    else zero(w->c);

    MR_OUT
}
