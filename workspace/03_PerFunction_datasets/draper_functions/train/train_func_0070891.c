FindMatchingPoint(int ptindex,SplineSet *ss) {
    SplinePoint *sp;

    if( ptindex==0 )
return( NULL );
    for ( ; ss!=NULL; ss=ss->next ) {
	for ( sp=ss->first; ; ) {
	    if ( sp->ptindex == ptindex )
return( sp );
	    if ( sp->next == NULL )
	break;
	    sp = sp->next->to;
	    if ( sp==ss->first )
	break;
	}
    }
return( NULL );
}
