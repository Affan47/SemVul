gdraw_32_on_8_nomag_nodithered_masked(GXDisplay *gdisp, GImage *image, GRect *src) {
    int i,j;
    struct _GImage *base = image->list_len==0?image->u.image:image->u.images[0];
    int trans = base->trans;
    uint32 *pt, index;
    register uint8 *ipt, *mpt;
#if FAST_BITS
    int mbit;
#endif

    for ( i=src->y; i<src->y+src->height; ++i ) {
	pt = (uint32 *) (base->data + i*base->bytes_per_line) + src->x;
	ipt = (uint8 *) (gdisp->gg.img->data) + (i-src->y)*gdisp->gg.img->bytes_per_line;
	mpt = (uint8 *) (gdisp->gg.mask->data) + (i-src->y)*gdisp->gg.mask->bytes_per_line;
#if FAST_BITS
	if ( gdisp->gg.mask->bitmap_bit_order == MSBFirst )
	    mbit = 0x80;
	else
	    mbit = 0x1;
#endif
	for ( j=src->width-1; j>=0; --j ) {
	    index = *pt++;
	    if ( index==trans ) {
#if FAST_BITS==0
		*mpt++ = 0xff;
#else
		*mpt |= mbit;
#endif
		*ipt++ = 0x00;
	    } else {
		*ipt++ = _GXDraw_GetScreenPixel(gdisp,index);
#if FAST_BITS==0
		*mpt++ = 0;
#else
		*mpt &= ~mbit;
#endif
	    }
#if FAST_BITS
	    if ( gdisp->gg.mask->bitmap_bit_order == MSBFirst ) {
		if (( mbit>>=1 )==0 ) {mbit=0x80; ++mpt;};
	    } else {
		if (( mbit<<=1 )==256 ) {mbit=0x1; ++mpt;};
	    }
#endif
	}
    }
}
