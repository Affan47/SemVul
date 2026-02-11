SplinePointListCopySelected(SplinePointList *base) {
    SplinePointList *head=NULL, *last=NULL, *cur=NULL;
    SplinePoint *pt, *first;
    int anysel, allsel;

    for ( ; base!=NULL; base = base->next ) {
	anysel = false; allsel = true;
	first = NULL;
	for ( pt=base->first; pt!=NULL && pt!=first; pt = pt->next->to ) {
	    if ( pt->selected ) anysel = true;
	    else allsel = false;
	    if ( first==NULL ) first = pt;
	    if ( pt->next==NULL )
	break;
	}
	if ( allsel )
	    cur = SplinePointListCopy1(base);
	else if ( anysel )
	    cur = SplinePointListCopySelected1(base);
	if ( anysel ) {
	    if ( head==NULL )
		head = cur;
	    else
		last->next = cur;
	    for ( last = cur; last->next ; last = last->next );
	}
    }
return( head );
}
