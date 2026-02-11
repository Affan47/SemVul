AnchorClassMkMkMatch(SplineChar *sc1,SplineChar *sc2,
	AnchorPoint **_ap1,AnchorPoint **_ap2 ) {
    AnchorPoint *ap1, *ap2;

    for ( ap1=sc1->anchor; ap1!=NULL ; ap1=ap1->next ) {
	for ( ap2=sc2->anchor; ap2!=NULL; ap2=ap2->next ) {
	    if ( ap1->anchor==ap2->anchor &&
		    ap1->type==at_basemark && ap2->type==at_mark)  {
		 *_ap1 = ap1;
		 *_ap2 = ap2;
return( ap1->anchor );
	    }
	}
    }
return( NULL );
}
