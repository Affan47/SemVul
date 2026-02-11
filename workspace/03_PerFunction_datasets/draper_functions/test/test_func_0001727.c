leader_speaks(mtmp)
	register struct monst *mtmp;
{

	if(!mtmp->mpeaceful) {
		Qstat(pissed_off) = TRUE;
		mtmp->mstrategy &= ~STRAT_WAITMASK;
	}


	if (!on_level(&u.uz, &qstart_level)) return;

	if(Qstat(pissed_off)) {
	  qt_pager(QT_LASTLEADER);
	  expulsion(TRUE);
	} else chat_with_leader();
}
