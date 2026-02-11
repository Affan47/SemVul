image_16BGR555_to_24BGR(int width, unsigned char *dest, unsigned char *source)
{
    int i;
    WORD w;
    unsigned char value;
    for (i=0; i<width; i++) {
	w = (WORD)(source[0] + (source[1] << 8));
	value =   (unsigned char)(w & 0x1f);
	*dest++ = (unsigned char)((value << 3) + (value >> 2));
	value =   (unsigned char)((w >> 5) & 0x1f);
	*dest++ = (unsigned char)((value << 3) + (value >> 2));
	value =   (unsigned char)((w >> 10) & 0x1f);
	*dest++ = (unsigned char)((value << 3) + (value >> 2));
	source += 2;
    }
}
