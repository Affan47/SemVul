gdraw_32_on_16_nomag_nomask(GXDisplay *gdisp, GImage *image, GRect *src) {
    int i,j;
    struct _GImage *base = image->list_len==0?image->u.image:image->u.images[0];
    register uint32 *pt, index;
    register uint16 *ipt;
    int endian_mismatch = gdisp->endian_mismatch;

    for ( i=src->y; i<src->y+src->height; ++i ) {
	pt = (uint32 *) (base->data + i*base->bytes_per_line) + src->x;
	ipt = (uint16 *) (gdisp->gg.img->data + (i-src->y)*gdisp->gg.img->bytes_per_line);
	for ( j=src->width-1; j>=0; --j ) {
	    index = *pt++;
	    *ipt++ = Pixel16(gdisp,index);
	    if ( endian_mismatch )
		ipt[-1] = FixEndian16(ipt[-1]);
	}
    }
}
