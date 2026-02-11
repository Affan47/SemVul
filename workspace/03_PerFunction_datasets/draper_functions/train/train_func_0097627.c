AnySelectedHints(FontViewBase *fv) {
    SplineFont *sf = fv->sf;
    int gid, enc;
    SplineChar *sc;

    for ( enc=0; enc<fv->map->enccount; ++enc ) {
	if ( fv->selected[enc] && (gid=fv->map->map[enc])!=-1 &&
		(sc = sf->glyphs[gid])!=NULL &&
		(sc->hstem!=NULL || sc->vstem!=NULL || sc->dstem!=NULL ))
return( true );
    }

return( false );
}
