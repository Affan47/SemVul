PtMovesInitToContour(struct ptmoves *ptmoves,SplineSet *ss) {
    int cnt;
    SplinePoint *sp;
    BasePoint dir1, dir2;
    double len;

    for ( cnt=0, sp=ss->first; ; ) {
	ptmoves[cnt].sp = sp;
	ptmoves[cnt].newpos = sp->me;
	ptmoves[cnt].touched = false;
	if ( sp->nonextcp ) {
	    dir1.x = sp->next->to->me.x - sp->me.x;
	    dir1.y = sp->next->to->me.y - sp->me.y;
	} else {
	    dir1.x = sp->nextcp.x - sp->me.x;
	    dir1.y = sp->nextcp.y - sp->me.y;
	}
	len = dir1.x*dir1.x + dir1.y*dir1.y;
	if ( len!=0 ) {
	    len = sqrt(len);
	    dir1.x /= len;
	    dir1.y /= len;
	}
	ptmoves[cnt].ndir = dir1;
	if ( dir1.x<0 ) dir1.x = -dir1.x;

	if ( sp->noprevcp ) {
	    dir2.x = sp->prev->from->me.x - sp->me.x;
	    dir2.y = sp->prev->from->me.y - sp->me.y;
	} else {
	    dir2.x = sp->prevcp.x - sp->me.x;
	    dir2.y = sp->prevcp.y - sp->me.y;
	}
	len = dir2.x*dir2.x + dir2.y*dir2.y;
	if ( len!=0 ) {
	    len = sqrt(len);
	    dir2.x /= len;
	    dir2.y /= len;
	}
	ptmoves[cnt].pdir = dir2;
	if ( dir2.x<0 ) dir2.x = -dir2.x;

	ptmoves[cnt].factor = dir1.x>dir2.x ? dir1.x : dir2.x;

	sp = sp->next->to; ++cnt;
	if ( sp==ss->first )
    break;
    }
    ptmoves[cnt] = ptmoves[0];
return( cnt );
}
