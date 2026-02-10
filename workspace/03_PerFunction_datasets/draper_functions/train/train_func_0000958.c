ISolveWithin(const Spline *spline,int major,
	extended val,extended tlow, extended thigh) {
    Spline1D temp;
    extended ts[3];
    const Spline1D *sp = &spline->splines[major];
    int i;


    if ( tlow==0 && val==(&spline->from->me.x)[major] )
return( 0 );
    if ( thigh==1.0 && val==(&spline->to->me.x)[major] )
return( 1.0 );

    temp = *sp;
    temp.d -= val;
    IterateSolve(&temp,ts);
    if ( tlow<thigh ) {
	for ( i=0; i<3; ++i )
	    if ( ts[i]>=tlow && ts[i]<=thigh )
return( ts[i] );
	for ( i=0; i<3; ++i ) {
	    if ( ts[i]>=tlow-1./1024. && ts[i]<=tlow )
return( tlow );
	    if ( ts[i]>=thigh && ts[i]<=thigh+1./1024 )
return( thigh );
	}
    } else {
	for ( i=0; i<3; ++i )
	    if ( ts[i]>=thigh && ts[i]<=tlow )
return( ts[i] );
	for ( i=0; i<3; ++i ) {
	    if ( ts[i]>=thigh-1./1024. && ts[i]<=thigh )
return( thigh );
	    if ( ts[i]>=tlow && ts[i]<=tlow+1./1024 )
return( tlow );
	}
    }
return( -1 );
}
