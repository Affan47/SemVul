rgb32_to_rgb24(unsigned char* restrict dest, unsigned char* restrict src,
	       int p)
{
    register unsigned char* restrict s = src;
    register unsigned char* restrict d = dest;

    while (p--) {
	s++;
	*(d++) = *(s++);
	*(d++) = *(s++);
	*(d++) = *(s++);
    }
}
