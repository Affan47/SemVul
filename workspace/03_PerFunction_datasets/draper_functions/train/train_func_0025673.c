SPLsStartToLeftmost(SplineChar *sc,int layer) {
    int changed = 0;
    SplineSet *ss;

    if ( sc==NULL )
return;

    if ( sc->parent->multilayer ) {
	for ( layer=ly_fore; layer<sc->layer_cnt; ++layer ) {
	    for ( ss = sc->layers[layer].splines; ss!=NULL; ss=ss->next )
		SPLStartToLeftmost(sc,ss,&changed);
	}
	if ( changed )
	    SCCharChangedUpdate(sc,ly_all);
    } else {
	for ( ss = sc->layers[layer].splines; ss!=NULL; ss=ss->next )
	    SPLStartToLeftmost(sc,ss,&changed);
	if ( changed )
	    SCCharChangedUpdate(sc,layer);
    }
}
