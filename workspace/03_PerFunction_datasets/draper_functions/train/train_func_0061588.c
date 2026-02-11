findpriest(roomno)
char roomno;
{
	register struct monst *mtmp;

	for(mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
	    if (DEADMONSTER(mtmp)) continue;
	    if(mtmp->ispriest && (EPRI(mtmp)->shroom == roomno) &&
	       histemple_at(mtmp,mtmp->mx,mtmp->my))
		return(mtmp);
	}
	return (struct monst *)0;
}
