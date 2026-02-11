_SCMakeDotless(SplineFont *sf, SplineChar *dotless, int layer, int doit) {
    SplineChar *sc, *xsc;
    BlueData bd;
    SplineSet *head=NULL, *last=NULL, *test, *cur, *next;
    DBounds b;

    sc = SFGetChar(sf,dotless->unicodeenc==0x131?'i':'j',NULL);
    xsc = SFGetChar(sf,'x',NULL);
    if ( sc==NULL || sc->layers[layer].splines==NULL || sc->layers[layer].refs!=NULL || xsc==NULL )
return( false );
    QuickBlues(sf,layer,&bd);
    if ( bd.xheight==0 )
return(false );
    for ( test=sc->layers[layer].splines; test!=NULL; test=test->next ) {
	next = test->next; test->next = NULL;
	SplineSetQuickBounds(test,&b);
	test->next = next;
	if ( b.miny < bd.xheight ) {
	    if ( !doit )
return( true );
	    cur = SplinePointListCopy1(test);
	    if ( last==NULL )
		head = cur;
	    else
		last->next = cur;
	    last = cur;
	}
    }
    if ( head==NULL )
return( false );

    SCPreserveLayer(dotless,layer,true);
    SplinePointListsFree(dotless->layers[layer].splines);
    dotless->layers[layer].splines = NULL;
    SCRemoveLayerDependents(dotless,layer);
    dotless->width = sc->width;
    dotless->layers[layer].splines = head;
    SCCharChangedUpdate(dotless,layer);
return( true );
}
