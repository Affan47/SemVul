PickGreyClut(GClut *clut,int clutmax,char *grey_clut,int tot) {
    int i,j;

    clut->trans_index = COLOR_UNKNOWN;
    if ( clutmax==256 ) {
	for ( i=0; i<256; ++i )
	    clut->clut[i] = COLOR_CREATE(i,i,i);
	clut->clut_len = 256;
    } else if ( tot<=clutmax ) {
	for ( i=j=0; i<256; ++i )
	    if ( grey_clut[i] )
		clut->clut[j++] = COLOR_CREATE(i,i,i);
	clut->clut_len = j;
    } else {
	int min_val, max_val;
	int incr;

	for ( i=0; i<256 && !grey_clut[i]; ++i );
	min_val = i;
	for ( i=255; i>=0 && !grey_clut[i]; --i );
	max_val = i+1;
	incr = (max_val-min_val)/(clutmax-1);
	for ( i=0; i<clutmax; ++i )
	    clut->clut[i] = COLOR_CREATE(min_val+i*incr,min_val+i*incr,min_val+i*incr);
	clut->clut[i-1] = COLOR_CREATE(max_val,max_val,max_val);
	clut->clut_len = clutmax;
    }
    clut->is_grey = true;
return( clut );
}
