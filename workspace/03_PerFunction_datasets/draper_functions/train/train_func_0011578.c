CubicSolve(const Spline1D *sp,bigreal sought, extended ts[3]) {
    extended t;
    extended ts2[3];
    int i,j;


    ts[0] = ts[1] = ts[2] = -1;
    if ( !_CubicSolve(sp,sought,ts2)) {
return( false );
    }

    for ( i=j=0; i<3; ++i ) {
	if ( ts2[i]>-.0001 && ts2[i]<1.0001 ) {
	    if ( ts2[i]<0 ) ts[j++] = 0;
	    else if ( ts2[i]>1 ) ts[j++] = 1;
	    else
		ts[j++] = ts2[i];
	}
    }
    if ( j==0 )
return( false );

    if ( ts[0]>ts[2] && ts[2]!=-1 ) {
	t = ts[0]; ts[0] = ts[2]; ts[2] = t;
    }
    if ( ts[0]>ts[1] && ts[1]!=-1 ) {
	t = ts[0]; ts[0] = ts[1]; ts[1] = t;
    }
    if ( ts[1]>ts[2] && ts[2]!=-1 ) {
	t = ts[1]; ts[1] = ts[2]; ts[2] = t;
    }
return( true );
}
