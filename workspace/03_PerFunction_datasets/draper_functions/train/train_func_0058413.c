BDFMakeChar(BDFFont *bdf,EncMap *map,int enc) {
    SplineFont *sf=bdf->sf;

    if ( enc==-1 )
return( NULL );

    if ( sf->cidmaster!=NULL ) {
	int j = SFHasCID(sf,enc);
	sf = sf->cidmaster;
	if ( j==-1 ) {
	    for ( j=0; j<sf->subfontcnt; ++j )
		if ( enc<sf->subfonts[j]->glyphcnt )
	    break;
	    if ( j==sf->subfontcnt )
return( NULL );
	}
	sf = sf->subfonts[j];
    }
    SFMakeChar(sf,map,enc);
return( BDFMakeGID(bdf,map->map[enc]));
}
