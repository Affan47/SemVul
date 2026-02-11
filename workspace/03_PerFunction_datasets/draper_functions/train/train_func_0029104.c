strong_bigrand(_MIPD_ csprng *rng,big w,big x)
{
	int i, m;
	mr_small r;
    unsigned int ran;
    unsigned int ch;

#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    MR_IN(20)

	m = 0;
    zero(mr_mip->w1);

    do
    {
		m++;
		mr_mip->w1->len=m;
		for (r = 0, i = 0; i < sizeof(mr_small); i++) {
			ch=(unsigned char)strong_rng(rng);
			ran=ch;
			r = (r << 8) ^ ran;
		}
        if (mr_mip->base==0) mr_mip->w1->w[m-1]=r;
        else                 mr_mip->w1->w[m-1]=MR_REMAIN(r,mr_mip->base);
    } while (mr_compare(mr_mip->w1,w)<0);
	mr_lzero(mr_mip->w1);
    divide(_MIPP_ mr_mip->w1,w,w);

    copy(mr_mip->w1,x);
    MR_OUT
}
