UFORefFixup(SplineFont *sf, SplineChar *sc ) {
    RefChar *r, *prev;
    SplineChar *rsc;

    if ( sc==NULL || sc->ticked )
return;
    sc->ticked = true;
    prev = NULL;
    for ( r=sc->layers[ly_fore].refs; r!=NULL; r=r->next ) {
	rsc = SFGetChar(sf,-1,(char *) (r->sc));
	if ( rsc==NULL ) {
	    LogError( _("Failed to find glyph %s when fixing up references\n"), (char *) r->sc );
	    if ( prev==NULL )
		sc->layers[ly_fore].refs = r->next;
	    else
		prev->next = r->next;
	    free((char *) r->sc);

	} else {
	    UFORefFixup(sf,rsc);
	    free((char *) r->sc);
	    r->sc = rsc;
	    prev = r;
	    SCReinstanciateRefChar(sc,r,ly_fore);
	}
    }
}
