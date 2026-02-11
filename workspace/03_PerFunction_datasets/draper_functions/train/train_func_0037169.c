SplineSetsRemoveAnnoyingExtrema(SplineSet *ss,bigreal err) {
    int changed = false;
    bigreal err_sq = err*err;
    Spline *s, *first;


    while ( ss!=NULL ) {
	first = NULL;
	for ( s = ss->first->next; s!=NULL && s!=first; s = s->to->next ) {
	    if ( first == NULL ) first = s;
	    if ( SplineRemoveAnnoyingExtrema(s,err_sq))
		changed = true;
	}
	ss = ss->next;
    }
return( changed );
}
