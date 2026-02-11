FVDetachAndRemoveGlyphs(FontViewBase *fv) {
    int i, j, gid;
    EncMap *map = fv->map;
    SplineFont *sf = fv->sf;
    int flags = -1;
    int changed = false, altered = false;
    FontViewBase *fvs;

    for ( i=0; i<map->enccount; ++i ) if ( fv->selected[i] && (gid=map->map[i])!=-1 ) {
	altered = true;
	map->map[i] = -1;
	if ( map->backmap[gid]==i ) {
	    for ( j=map->enccount-1; j>=0 && map->map[j]!=gid; --j );
	    map->backmap[gid] = j;
	    if ( j==-1 ) {
		SFRemoveGlyph(sf,sf->glyphs[gid],&flags);
		changed = true;
	    } else if ( sf->glyphs[gid]!=NULL && sf->glyphs[gid]->altuni != NULL && map->enc!=&custom )
		AltUniRemove(sf->glyphs[gid],UniFromEnc(i,map->enc));
	}
    }
    if ( changed && !fv->sf->changed ) {
	fv->sf->changed = true;
	for ( fvs=sf->fv; fvs!=NULL; fvs=fvs->nextsame )
	    FVSetTitle(fvs);
    }
    if ( altered )
	FVRefreshAll(sf);
}
