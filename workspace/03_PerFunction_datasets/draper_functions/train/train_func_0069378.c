pdp_imageproc_hardthresh_process(void *x, u32 width, u32 height, s16 *image)
{
    int i;
    uptr thresh = (uptr)x;
    s32 sign1, isign2, a;
    s32 *wimage = (s32 *)image;
    int wsize = (width * height) >> 1;
    thresh |= (thresh << 16);
    for (i=0; i<wsize; i++){
	a = wimage[i];
	sign1 = _sign(a);
	a ^= sign1;
	_decouple(&a);
	a -= thresh;
	isign2 = ~ _sign(a);
	a &= isign2;
	_decouple(&a);
	a += thresh & isign2;
	a ^= sign1;
	wimage[i] = a;
    }
}
