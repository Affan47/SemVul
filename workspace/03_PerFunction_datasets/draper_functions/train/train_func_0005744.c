mon_is_local(mon)
struct monst *mon;
{
    struct monst *curr;

    for (curr = migrating_mons; curr; curr = curr->nmon)
	if (curr == mon) return FALSE;

    for (curr = mydogs; curr; curr = curr->nmon)
	if (curr == mon) return FALSE;
    return TRUE;
}
