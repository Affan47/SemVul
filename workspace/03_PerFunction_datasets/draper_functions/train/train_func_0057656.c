_AnchorClassUnused(SplineChar *sc,int *waslig, int classmatch) {
    AnchorClass *an, *maybe;
    int val, maybelig;
    SplineFont *sf;
    int ismarkglyph, isligatureglyph;
    PST *pst;


    ismarkglyph = (sc->width==0) || sc->glyph_class==(3+1) ||
	    ( sc->unicodeenc!=-1 && sc->unicodeenc<0x10000 && iscombining(sc->unicodeenc)) ||
	    ( sc->anchor!=NULL && (sc->anchor->type == at_mark || sc->anchor->type == at_basemark));
    for ( pst = sc->possub; pst!=NULL && pst->type!=pst_ligature; pst=pst->next );
    isligatureglyph = (pst!=NULL) || sc->glyph_class==2+1;

    *waslig = false; maybelig = false; maybe = NULL;
    sf = sc->parent;
    if ( sf->cidmaster!=NULL ) sf = sf->cidmaster;
    for ( an=sf->anchor; an!=NULL; an=an->next ) {
	if ( classmatch ) {
	    if (( an->type == act_mklg && !isligatureglyph && !ismarkglyph ) ||
		    ( an->type == act_mkmk && !ismarkglyph ))
    continue;
	}
	val = IsAnchorClassUsed(sc,an);
	if ( val>=0 ) {
	    *waslig = val;
return( an );
	} else if ( val!=-1 && maybe==NULL ) {
	    maybe = an;
	    maybelig = val;
	}
    }
    *waslig = maybelig;
return( maybe );
}
