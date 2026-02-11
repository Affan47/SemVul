ttfdumpf1_6bchar(FILE *bdat, BDFChar *bc,BDFFont *bdf) {

    int32 pos = ftell(bdat);
    int r,c,val;

    if ( bdf->sf->hasvmetrics )
	ttfdumpbigmetrics(bdat,bc);
    else
	ttfdumpsmallmetrics(bdat,bc);


    for ( r=0; r<=bc->ymax-bc->ymin; ++r ) {
	if ( bdf->clut==NULL || bdf->clut->clut_len==256 ) {
	    for ( c=0; c<bc->bytes_per_line; ++c )
		putc(bc->bitmap[r*bc->bytes_per_line+c],bdat);
	} else if ( bdf->clut->clut_len==4 ) {
	    for ( c=0; c<bc->bytes_per_line; c+=2 ) {
		val = bc->bitmap[r*bc->bytes_per_line+c]<<4;
		if ( c+1<bc->bytes_per_line )
		    val += bc->bitmap[r*bc->bytes_per_line+c+1];
		putc(val,bdat);
	    }
	} else {
	    for ( c=0; c<bc->bytes_per_line; c+=4 ) {
		val = bc->bitmap[r*bc->bytes_per_line+c]<<6;
		if ( c+1<bc->bytes_per_line )
		    val += bc->bitmap[r*bc->bytes_per_line+c+1]<<4;
		if ( c+2<bc->bytes_per_line )
		    val += bc->bitmap[r*bc->bytes_per_line+c+2]<<2;
		if ( c+3<bc->bytes_per_line )
		    val += bc->bitmap[r*bc->bytes_per_line+c+3];
		putc(val,bdat);
	    }
	}
    }
return( pos );
}
