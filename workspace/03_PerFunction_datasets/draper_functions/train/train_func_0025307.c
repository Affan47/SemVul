ftrunc(_MIPD_ flash x,big y,flash z)
{

#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(45)
    numer(_MIPP_ x,mr_mip->w1);
    denom(_MIPP_ x,mr_mip->w2);
    divide(_MIPP_ mr_mip->w1,mr_mip->w2,mr_mip->w3);
    copy(mr_mip->w3,y);
    if (y!=z) fpack(_MIPP_ mr_mip->w1,mr_mip->w2,z);
    MR_OUT
}
