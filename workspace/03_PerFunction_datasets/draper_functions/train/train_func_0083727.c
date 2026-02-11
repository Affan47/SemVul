RealApprox(real a,real b) {

    if ( a==0 ) {
	if ( b<.0001 && b>-.0001 )
return( true );
    } else if ( b==0 ) {
	if ( a<.0001 && a>-.0001 )
return( true );
    } else {
	a /= b;
	if ( a>=.95 && a<=1.05 )
return( true );
    }
return( false );
}
