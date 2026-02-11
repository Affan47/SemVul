SplineRemoveExtremaTooClose(Spline1D *sp, extended *_t1, extended *_t2 ) {
    extended last, test;
    extended t1= *_t1, t2 = *_t2;

    if ( t1>t2 && t2!=-1 ) {
	t1 = t2;
	t2 = *_t1;
    }
    last = sp->d;
    if ( t1!=-1 ) {
	test = ((sp->a*t1+sp->b)*t1+sp->c)*t1+sp->d;
	if ( (test-last)*(test-last)<1 )
	    t1 = -1;
	else
	    last = test;
    }
    if ( t2!=-1 ) {
	test = ((sp->a*t2+sp->b)*t2+sp->c)*t2+sp->d;
	if ( (test-last)*(test-last)<1 )
	    t2 = -1;
	else
	    last = test;
    }
    test = sp->a+sp->b+sp->c+sp->d;
    if ( (test-last)*(test-last)<1 ) {
	if ( t2!=-1 )
	    t2 = -1;
	else if ( t1!=-1 )
	    t1 = -1;
	else
	    ;
    }
    *_t1 = t1; *_t2 = t2;
}
