gdraw_32a_on_1_nomag_dithered(GXDisplay *gdisp, GImage *image, GRect *src) {
    int i,j,end;
    unsigned int index;
    struct _GImage *base = image->list_len==0?image->u.image:image->u.images[0];
    int trans = base->trans;
    uint32 *pt;
    uint8 *ipt, *mpt;
    short *g_d;
    register int gd;
    int bit;

    for ( i=src->width-1; i>=0; --i )
	gdisp->gg.green_dith[i] = 0;

    end = src->width;
    for ( i=src->y; i<src->y+src->height; ++i ) {
	pt = (uint32 *) (base->data + i*base->bytes_per_line) + src->x;
	ipt = (uint8 *) (gdisp->gg.img->data) + (i-src->y)*gdisp->gg.img->bytes_per_line;
	mpt = (uint8 *) (gdisp->gg.mask->data) + (i-src->y)*gdisp->gg.mask->bytes_per_line;
	if ( gdisp->gg.img->bitmap_bit_order == MSBFirst )
	    bit = 0x80;
	else
	    bit = 0x1;
	gd = 0;
	g_d = gdisp->gg.green_dith;
	for ( j=src->width-1; j>=0; --j ) {
	    index = *pt++;
	    if ( index==trans || (index>>24)<0x80 ) {
		*mpt |= bit;
		*ipt &= ~bit;
		++g_d;
	    } else {
		*mpt &= ~bit;
		gd += *g_d + COLOR_RED(index) + COLOR_GREEN(index) + COLOR_BLUE(index);
		if ( gd<3*128 ) {
		    *ipt &= ~bit;
		    *g_d++ = gd /= 2;
		} else {
		    *ipt |= bit;
		    *g_d++ = gd = (gd - 3*255)/2;
		}
	    }
	    if ( gdisp->gg.img->bitmap_bit_order == MSBFirst ) {
		if (( bit>>=1 )==0 ) {bit=0x80; ++ipt; ++mpt;};
	    } else {
		if (( bit<<=1 )==256 ) {bit=0x1; ++ipt; ++mpt;};
	    }
	}
    }
}
