MakeParallelogram(Spline *e11, Spline *e12, Spline *e21, Spline *e22,
	SplinePoint *mobile) {


    Spline *temp;
    SplinePoint *other1, *other2, *unconnected;
    double denom;

    if ( e11->to==mobile || e11->from==mobile ) {
	temp = e11;
	e11 = e12;
	e12 = temp;
    }
    if ( e21->to==mobile || e21->from==mobile ) {
	temp = e21;
	e21 = e22;
	e22 = temp;
    }

    other1 = e12->from==mobile ? e12->to : e12->from;
    other2 = e22->from==mobile ? e22->to : e22->from;
    unconnected = e11->from==other2 ? e11->to : e11->from;

    denom = (unconnected->me.y-other1->me.y)*(unconnected->me.x-other2->me.x) -
	    (unconnected->me.y-other2->me.y)*(unconnected->me.x-other1->me.x);
    if ( denom>-.0001 && denom<.0001 ) {


	mobile->me = unconnected->me;
    } else {
	mobile->me.y =
	    ((other2->me.x-other1->me.x)*(unconnected->me.y-other1->me.y)*
		    (unconnected->me.y-other2->me.y) -
		other2->me.y*(unconnected->me.y-other2->me.y)*(unconnected->me.x-other1->me.x) +
		other1->me.y*(unconnected->me.y-other1->me.y)*(unconnected->me.x-other2->me.x))/
	     denom;
	if ( unconnected->me.y-other1->me.y==0 )
	    mobile->me.x = other1->me.x + (unconnected->me.x-other2->me.x)/(unconnected->me.y-other2->me.y)*
		    (mobile->me.y-other1->me.y);
	else
	    mobile->me.x = other2->me.x + (unconnected->me.x-other1->me.x)/(unconnected->me.y-other1->me.y)*
		    (mobile->me.y-other2->me.y);
    }
    mobile->nextcp = mobile->prevcp = mobile->me;
    SplineRefigure(mobile->prev);
    SplineRefigure(mobile->next);
}
