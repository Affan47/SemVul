StemMoveDBottomEndTo(SplinePoint *sp,double y,DStemInfo *d,
	int is_start) {
    SplinePoint *other;
    double xoff;

    xoff = (y-sp->me.y)*d->unit.x/d->unit.y;
    if ( is_start ) {
	if ( sp->noprevcp || y>=sp->me.y ) {
	    sp->prevcp.y += (y-sp->me.y);
	    sp->prevcp.x += xoff;
	    if ( sp->prev->order2 && !sp->prev->from->nonextcp )
		sp->prev->from->nextcp = sp->prevcp;
	    sp->me.y = y;
	    sp->me.x += xoff;
	    SplineRefigure(sp->prev);
	} else {
	    other = SplinePointCreate(sp->me.x+xoff,y);
	    sp->nonextcp = true;
	    SplineMake(sp,other,sp->prev->order2);
	    sp = other;
	}
    } else {
	if ( sp->nonextcp || y>=sp->me.y ) {
	    sp->nextcp.y += (y-sp->me.y);
	    sp->nextcp.x += xoff;
	    if ( sp->next->order2 && !sp->next->to->noprevcp )
		sp->next->to->prevcp = sp->nextcp;
	    sp->me.y = y;
	    sp->me.x += xoff;
	    SplineRefigure(sp->next);
	} else {
	    other = SplinePointCreate(sp->me.x+xoff,y);
	    sp->noprevcp = true;
	    SplineMake(other,sp,sp->next->order2);
	    sp = other;
	}
    }
return( sp );
}
