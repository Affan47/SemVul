tester(SplineChar *sc, struct lookup_subtable *sub) {
    PST *pst;
    KernPair *kp;
    int isv;
    AnchorPoint *ap;

    if ( sc==NULL )
return( false );

    for ( ap=sc->anchor; ap!=NULL; ap=ap->next )
	if ( ap->anchor->subtable == sub )
return( true );
    for ( pst=sc->possub; pst!=NULL; pst=pst->next )
	if ( pst->subtable==sub )
return( true );
    for ( isv=0; isv<2; ++isv )
	for ( kp = isv ? sc->vkerns : sc->kerns; kp!=NULL; kp=kp->next )
	    if ( kp->subtable == sub )
return( true );

return( false );
}
