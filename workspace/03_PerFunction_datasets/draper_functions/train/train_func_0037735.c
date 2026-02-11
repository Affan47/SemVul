InitTrueColor(GXDisplay *gdisp) {
    Visual *vis = gdisp->visual;
    int red_shift, green_shift, blue_shift;
    int red_bits_shift, blue_bits_shift, green_bits_shift;


    for ( red_shift=0; red_shift<24 && !(vis->red_mask&(1<<red_shift)); ++red_shift );
    for ( green_shift=0; green_shift<24 && !(vis->green_mask&(1<<green_shift)); ++green_shift );
    for ( blue_shift=0; blue_shift<24 && !(vis->blue_mask&(1<<blue_shift)); ++blue_shift );
    gdisp->cs.red_shift = red_shift;
    gdisp->cs.green_shift = green_shift;
    gdisp->cs.blue_shift = blue_shift;

    gdisp->cs.red_bits_mask = vis->red_mask>>red_shift;
    gdisp->cs.green_bits_mask = vis->green_mask>>green_shift;
    gdisp->cs.blue_bits_mask = vis->blue_mask>>blue_shift;
    for ( red_bits_shift=0; gdisp->cs.red_bits_mask&(1<<red_bits_shift) ;
	    ++red_bits_shift );
    for ( green_bits_shift=0; gdisp->cs.green_bits_mask&(1<<green_bits_shift) ;
	    ++green_bits_shift );
    for ( blue_bits_shift=0; gdisp->cs.blue_bits_mask&(1<<blue_bits_shift) ;
	    ++blue_bits_shift );
    gdisp->cs.red_bits_shift = 24-red_bits_shift;
    gdisp->cs.green_bits_shift = 16-green_bits_shift;
    gdisp->cs.blue_bits_shift = 8-blue_bits_shift;

    gdisp->cs.alpha_bits = 0xffffffff&~(vis->red_mask|vis->green_mask|vis->blue_mask);
}
