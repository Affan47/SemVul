SplineCurvature(Spline *s, bigreal t) {

    bigreal dxdt, dydt, d2xdt2, d2ydt2, denom, numer;

    if ( s==NULL )
return( CURVATURE_ERROR );

    dxdt = (3*s->splines[0].a*t+2*s->splines[0].b)*t+s->splines[0].c;
    dydt = (3*s->splines[1].a*t+2*s->splines[1].b)*t+s->splines[1].c;
    d2xdt2 = 6*s->splines[0].a*t + 2*s->splines[0].b;
    d2ydt2 = 6*s->splines[1].a*t + 2*s->splines[1].b;
    denom = pow( dxdt*dxdt + dydt*dydt, 3.0/2.0 );
    numer = dxdt*d2ydt2 - dydt*d2xdt2;

    if ( numer==0 )
return( 0 );
    if ( denom==0 )
return( CURVATURE_ERROR );

return( numer/denom );
}
