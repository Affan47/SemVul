ecp_memkill(_MIPD_ char *mem,int num)
{
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif

    if (mem==NULL) return;

#ifndef MR_AFFINE_ONLY
    if (mr_mip->coord==MR_AFFINE)
        memset(mem,0,mr_ecp_reserve_a(num,mr_mip->nib-1));
    else
#endif
        memset(mem,0,mr_ecp_reserve(num,mr_mip->nib-1));


#ifndef MR_STATIC
    mr_free(mem);
#endif
}
