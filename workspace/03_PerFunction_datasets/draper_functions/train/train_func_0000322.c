SPLAverageCps(SplinePointList *spl) {
    SplinePoint *sp;

    while ( spl!=NULL ) {
	for ( sp=spl->first ; ; ) {
	    SPAverageCps(sp);
	    if ( sp->next==NULL )
	break;
	    sp = sp->next->to;
	    if ( sp==spl->first )
	break;
	}
	spl = spl->next;
    }
}
