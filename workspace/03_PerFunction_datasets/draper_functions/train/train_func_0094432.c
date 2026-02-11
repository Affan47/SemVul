FillLineMetrics(struct bitmapSizeTable *size,BDFFont *bdf) {
    int i, first;
    BDFChar *bc;

    memset(&size->hori,0,sizeof(struct sbitLineMetrics));
    memset(&size->vert,0,sizeof(struct sbitLineMetrics));


    size->hori.caretRise = 1;
    size->vert.caretRise = 1;
    first = true;
    for ( i=0; i<bdf->glyphcnt ; ++i ) if ( (bc=bdf->glyphs[i])!=NULL ) {
	if ( first ) {


	    size->hori.widthMax = bc->xmax-bc->xmin+1;
	    size->hori.minoriginsb = bc->xmin;
	    size->hori.minAdvancesb = bc->width-bc->xmax;
	    size->hori.minafterbl = bc->ymin;
	    size->hori.maxbeforebl = bc->ymax;
	    first = false;
	} else {


	    if ( bc->xmax-bc->xmin+1 > size->hori.widthMax ) size->hori.widthMax = bc->xmax-bc->xmin+1;
	    if ( bc->xmin < size->hori.minoriginsb ) size->hori.minoriginsb = bc->xmin;
	    if ( bc->width-bc->xmax < size->hori.minAdvancesb ) size->hori.minAdvancesb = bc->width-bc->xmax;
	    if ( bc->ymin < size->hori.minafterbl ) size->hori.minafterbl = bc->ymin;
	    if ( bc->ymax+1 > size->hori.maxbeforebl ) size->hori.maxbeforebl = bc->ymax+1;
	}
    }
    size->hori.ascender = BdfPropHasInt(bdf,"FONT_ASCENT",bdf->ascent);
    size->hori.descender = -BdfPropHasInt(bdf,"FONT_DESCENT",bdf->descent);


#if 0
    size->vert.minoriginsb = size->hori.maxbeforebl;
    size->vert.minAdvancesb = size->hori.minafterbl;
#endif


    size->vert.ascender = bdf->pixelsize/2;
    size->vert.descender = -bdf->pixelsize/2;
    size->vert.widthMax = bdf->pixelsize;
}
