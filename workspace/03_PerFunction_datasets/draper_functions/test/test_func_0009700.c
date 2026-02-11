op_rotate_ccw(struct ida_image *src, struct ida_rect *rect,
	      unsigned char *dst, int line, void *data)
{
    char *pix;
    unsigned int i;

    pix = src->data + (src->i.width-line-1) * 3;
    for (i = 0; i < src->i.height; i++) {
	dst[0] = pix[0];
	dst[1] = pix[1];
	dst[2] = pix[2];
	pix += src->i.width * 3;
	dst += 3;
    }
}
