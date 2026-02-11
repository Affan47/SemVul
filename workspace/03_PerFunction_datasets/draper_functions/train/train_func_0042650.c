SetCurve(SplinePoint *sp,BasePoint *center,real xrad, real yrad,
	struct shapedescrip *pt_d) {
    sp->me.x = center->x+xrad*pt_d->me.x; sp->me.y = center->y+yrad*pt_d->me.y;
    sp->nextcp.x = center->x+xrad*pt_d->nextcp.x; sp->nextcp.y = center->y+yrad*pt_d->nextcp.y;
    sp->prevcp.x = center->x+xrad*pt_d->prevcp.x; sp->prevcp.y = center->y+yrad*pt_d->prevcp.y;
    sp->nonextcp = sp->noprevcp = (xrad==0 && yrad==0);
}
