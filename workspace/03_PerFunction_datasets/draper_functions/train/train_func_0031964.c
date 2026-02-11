haslcaret(SplineChar *sc) {
    PST *pst; int j;

    for ( pst=sc->possub; pst!=NULL && pst->type!=pst_lcaret; pst=pst->next );
    if ( pst!=NULL ) {
	if ( !sc->lig_caret_cnt_fixed ) {
	    for ( j=pst->u.lcaret.cnt-1; j>=0 && pst->u.lcaret.carets[j]==0; --j );
	    if ( j==-1 )
		pst = NULL;
	} else {
	    if ( pst->u.lcaret.cnt==0 )
		pst = NULL;
	}
    }
return( pst );
}
