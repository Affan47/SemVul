quest_stat_check(mtmp)
	struct monst *mtmp;
{
    if(mtmp->data->msound == MS_NEMESIS)
	Qstat(in_battle) = (mtmp->mcanmove && !mtmp->msleeping &&
			    monnear(mtmp, u.ux, u.uy));
}
