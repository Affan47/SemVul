makesflist(PyObject *item,enum bitmapformat bf) {
    struct sflist *ret = chunkalloc(sizeof( struct sflist ));
    ret->sf  = ((PyFF_Font *) item)->fv->sf;
    ret->map = ((PyFF_Font *) item)->fv->map;
    if ( bf==bf_ttf ) {
	int cnt;
	BDFFont *bdf;
	for ( cnt=0, bdf=ret->sf->bitmaps; bdf!=NULL; bdf=bdf->next, ++cnt );
	if ( cnt!=0 ) {
	    ret->sizes = galloc((cnt+1)*sizeof(int32));
	    ret->sizes[cnt] = 0;
	    for ( cnt=0, bdf=ret->sf->bitmaps; bdf!=NULL; bdf=bdf->next, ++cnt ) {
		if ( bdf->clut==NULL )
		    ret->sizes[cnt] = bdf->pixelsize;
		else
		    ret->sizes[cnt] = (BDFDepth(bdf)<<16) | bdf->pixelsize;
	    }
	}
    }
return( ret );
}
