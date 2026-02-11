SplineAtMinMax(Spline1D *sp, bigreal t ) {

return ( RealNear( (3*sp->a*t + 2*sp->b)*t + sp->c,0) &&
	    !RealNear( 6*sp->a*t + 2*sp->b, 0));
}
