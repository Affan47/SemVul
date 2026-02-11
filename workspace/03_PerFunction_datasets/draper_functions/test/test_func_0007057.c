SPLStartToLeftmost(SplineChar *sc,SplinePointList *spl, int *changed) {
    SplinePoint *sp;
    SplinePoint *best;

    if ( spl->first==spl->last ) {
	best = spl->first;
	for ( sp=spl->first; ; ) {
	    if ( sp->me.x < best->me.x ||
		    (sp->me.x==best->me.x && (fabs(sp->me.y)<fabs(best->me.y))) )
		best = sp;
	    if ( sp->next==NULL )
	break;
	    sp = sp->next->to;
	    if ( sp==spl->first )
	break;
	}
	if ( best!=spl->first ) {
	    if ( !*changed ) {
		SCPreserveState(sc,false);
		*changed = true;
	    }
	    SplineSetSpirosClear(spl);
	    spl->first = spl->last = best;
	}
    }
}
