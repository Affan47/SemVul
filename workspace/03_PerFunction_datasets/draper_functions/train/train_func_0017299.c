addmargin(double mf) {


    double range;


    if ( (logscale & x_axis) ) {
	if ( xmin  < min_double ) xmin = min_double;
	if ( xmax  < min_double ) xmax = min_double;
    }
    if ( (logscale & y_axis) ) {
	if ( ymin  < min_double ) ymin = min_double;
	if ( ymax  < min_double ) ymax = min_double;
    }

    if ( xautoscale ) {

	if ( logscale & x_axis) {
	    double b, t;


	    b = pow(xmax,-mf) / pow(xmin,(-mf-1));
	    t = pow(xmax,1+mf) / pow(xmin,mf);
	    xmin = b; xmax = t;
	} else {
	    range = xmax - xmin;
	    xmin = xmin - mf * range;
	    xmax = xmax + mf * range;
	}
    }

    if ( yautoscale ) {

	if ( logscale & y_axis) {
	    double b, t;


	    b = pow(ymax,-mf) / pow(ymin,(-mf-1));
	    t = pow(ymax,1+mf) / pow(ymin,mf);
	    ymin = b; ymax = t;
	} else {
	    range = ymax - ymin;
	    ymin = ymin - mf * range;
	    ymax = ymax + mf * range;
	}
    }


    if ( xmax == xmin) xmax += 1.0;
    if ( ymax == ymin) ymax += 1.0;
}
