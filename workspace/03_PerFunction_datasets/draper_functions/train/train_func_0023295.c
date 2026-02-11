CVFindCenter(CharView *cv, BasePoint *bp, int nosel) {
    DBounds b;
    ImageList *img;

    b.minx = b.miny = b.maxx = b.maxy = 0;
    SplineSetFindSelBounds(cv->b.layerheads[cv->b.drawmode]->splines,&b,nosel,cv->b.sc->inspiro&& hasspiro());
    if ( cv->b.drawmode==dm_fore ) {
	RefChar *rf;
	for ( rf=cv->b.layerheads[cv->b.drawmode]->refs; rf!=NULL; rf=rf->next ) {
	    if ( nosel || rf->selected ) {
		if ( b.minx==0 && b.maxx==0 )
		    b = rf->bb;
		else {
		    if ( rf->bb.minx<b.minx ) b.minx = rf->bb.minx;
		    if ( rf->bb.miny<b.miny ) b.miny = rf->bb.miny;
		    if ( rf->bb.maxx>b.maxx ) b.maxx = rf->bb.maxx;
		    if ( rf->bb.maxy>b.maxy ) b.maxy = rf->bb.maxy;
		}
	    }
	}
    }
    for ( img=cv->b.layerheads[cv->b.drawmode]->images; img!=NULL; img=img->next ) {
	if ( nosel || img->selected ) {
	    if ( b.minx==0 && b.maxx==0 )
		b = img->bb;
	    else {
		if ( img->bb.minx<b.minx ) b.minx = img->bb.minx;
		if ( img->bb.miny<b.miny ) b.miny = img->bb.miny;
		if ( img->bb.maxx>b.maxx ) b.maxx = img->bb.maxx;
		if ( img->bb.maxy>b.maxy ) b.maxy = img->bb.maxy;
	    }
	}
    }
    bp->x = (b.minx+b.maxx)/2;
    bp->y = (b.miny+b.maxy)/2;
}
