yuv_bgr24_c(SHORTLINEARGS)
{
    const yuv* s = (const yuv*) src;
    col* d = (col*) dest;

    while (w--)
	*d++ = *s++;
}
