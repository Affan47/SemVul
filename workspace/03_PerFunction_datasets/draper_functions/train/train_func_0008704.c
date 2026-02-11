SCHasSubs(SplineChar *sc, uint32 tag) {
    PST *pst;

    for ( pst=sc->possub; pst!=NULL; pst=pst->next ) {
	if ( pst->type==pst_substitution &&
		FeatureTagInFeatureScriptList(tag,pst->subtable->lookup->features) )
return( SFGetChar(sc->parent,-1,pst->u.subs.variant));
    }
return( NULL );
}
