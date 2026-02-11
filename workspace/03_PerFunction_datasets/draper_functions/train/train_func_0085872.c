restartcham()
{
	register struct monst *mtmp;

	for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
		if (DEADMONSTER(mtmp)) continue;
		mtmp->cham = pm_to_cham(monsndx(mtmp->data));
		if (mtmp->data->mlet == S_MIMIC && mtmp->msleeping &&
				cansee(mtmp->mx, mtmp->my)) {
			set_mimic_sym(mtmp);
			newsym(mtmp->mx,mtmp->my);
		}
	}
}
