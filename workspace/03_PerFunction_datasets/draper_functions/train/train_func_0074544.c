find_mid(unsigned nid, unsigned fmflags)
{
	struct monst *mtmp;

	if (!nid)
	    return &youmonst;
	if (fmflags & FM_FMON)
		for (mtmp = fmon; mtmp; mtmp = mtmp->nmon)
		    if (!DEADMONSTER(mtmp) && mtmp->m_id == nid) return mtmp;
	if (fmflags & FM_MIGRATE)
		for (mtmp = migrating_mons; mtmp; mtmp = mtmp->nmon)
	    	    if (mtmp->m_id == nid) return mtmp;
	if (fmflags & FM_MYDOGS)
		for (mtmp = mydogs; mtmp; mtmp = mtmp->nmon)
	    	    if (mtmp->m_id == nid) return mtmp;
	return (struct monst *) 0;
}
