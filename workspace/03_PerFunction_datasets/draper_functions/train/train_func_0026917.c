ecn2_get(_MIPD_ ecn2 *e,zzn2 *x,zzn2 *y,zzn2 *z)
{
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif

    zzn2_copy(&(e->x),x);
    zzn2_copy(&(e->y),y);
#ifndef MR_AFFINE_ONLY
    if (e->marker==MR_EPOINT_GENERAL) zzn2_copy(&(e->z),z);
    else                              zzn2_from_zzn(mr_mip->one,z);
#endif
}
