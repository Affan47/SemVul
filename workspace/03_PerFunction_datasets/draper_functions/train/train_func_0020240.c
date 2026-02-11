onscary(x, y, mtmp)
int x, y;
struct monst *mtmp;
{
	if (mtmp->isshk || mtmp->isgd || mtmp->iswiz || !mtmp->mcansee ||
	    mtmp->mpeaceful || mtmp->data->mlet == S_HUMAN ||
	    is_lminion(mtmp) || mtmp->data == &mons[PM_ANGEL] ||
	    is_rider(mtmp->data) || mtmp->data == &mons[PM_MINOTAUR])
		return(FALSE);

	return (boolean)(sobj_at(SCR_SCARE_MONSTER, x, y)
#ifdef ELBERETH
			 || sengr_at("Elbereth", x, y)
#endif
			 || (mtmp->data->mlet == S_VAMPIRE
			     && IS_ALTAR(levl[x][y].typ)));
}
