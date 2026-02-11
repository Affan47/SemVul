Spline2DFindPointsOfInflection(const Spline *sp, extended poi[2] ) {
    int cnt=0;
    extended a, b, c, b2_fourac, t;


    a = 3*((extended) sp->splines[1].a*sp->splines[0].b-(extended) sp->splines[0].a*sp->splines[1].b);
    b = 3*((extended) sp->splines[0].c*sp->splines[1].a - (extended) sp->splines[1].c*sp->splines[0].a);
    c = (extended) sp->splines[0].c*sp->splines[1].b-(extended) sp->splines[1].c*sp->splines[0].b;
    if ( !RealNear(a,0) ) {
	b2_fourac = b*b - 4*a*c;
	poi[0] = poi[1] = -1;
	if ( b2_fourac<0 )
return( 0 );
	b2_fourac = esqrt( b2_fourac );
	t = (-b+b2_fourac)/(2*a);
	if ( t>=0 && t<=1.0 )
	    poi[cnt++] = t;
	t = (-b-b2_fourac)/(2*a);
	if ( t>=0 && t<=1.0 ) {
	    if ( cnt==1 && poi[0]>t ) {
		poi[1] = poi[0];
		poi[0] = t;
		++cnt;
	    } else
		poi[cnt++] = t;
	}
    } else if ( !RealNear(b,0) ) {
	t = -c/b;
	if ( t>=0 && t<=1.0 )
	    poi[cnt++] = t;
    }
    if ( cnt<2 )
	poi[cnt] = -1;

return( cnt );
}
