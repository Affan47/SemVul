SCHasVertVariant(SplineChar *sc) {
    PST *pst;

    if ( sc==NULL )
return( NULL );

    for ( pst=sc->possub; pst!=NULL; pst=pst->next ) {
	if ( pst->type==pst_substitution &&
		(FeatureTagInFeatureScriptList(CHR('v','e','r','t'),pst->subtable->lookup->features) ||
		 FeatureTagInFeatureScriptList(CHR('v','r','t','2'),pst->subtable->lookup->features)) ) {
return( SFGetChar(sc->parent,-1,pst->u.subs.variant));
	}
    }
return( NULL );
}
