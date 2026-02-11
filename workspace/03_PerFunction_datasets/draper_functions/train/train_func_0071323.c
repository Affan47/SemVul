HasLigature(SplineChar *sc) {
    PST *pst, *best=NULL;
    int bestc=0,c;
    int32 univals[50];

    for ( pst=sc->possub; pst!=NULL; pst=pst->next ) {
	if ( pst->type==pst_ligature ) {
	    c = LigCnt(sc->parent,pst,univals,sizeof(univals)/sizeof(univals[0]));
	    if ( c>1 && c>bestc ) {
		c = bestc;
		best = pst;
	    }
	}
    }
return( best );
}
