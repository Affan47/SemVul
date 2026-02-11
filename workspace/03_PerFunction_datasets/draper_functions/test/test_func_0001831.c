xpm_znormalizeimagebits(bp, img)
    register unsigned char *bp;
    register XImage *img;
{
    register unsigned char c;

    switch (img->bits_per_pixel) {

    case 4:
	*bp = ((*bp >> 4) & 0xF) | ((*bp << 4) & ~0xF);
	break;

    case 16:
	c = *bp;
	*bp = *(bp + 1);
	*(bp + 1) = c;
	break;

    case 24:
	c = *(bp + 2);
	*(bp + 2) = *bp;
	*bp = c;
	break;

    case 32:
	c = *(bp + 3);
	*(bp + 3) = *bp;
	*bp = c;
	c = *(bp + 2);
	*(bp + 2) = *(bp + 1);
	*(bp + 1) = c;
	break;
    }
}
