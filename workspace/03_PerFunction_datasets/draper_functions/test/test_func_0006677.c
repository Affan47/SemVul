compute_tz_offset (struct tm *gmttm, struct tm *loctm)
{
	time_t lt, gt;
	if (! gmttm || !loctm)
		return G_MAXLONG;

	gmttm->tm_isdst = 0;
	loctm->tm_isdst = 0;

	lt = mktime (loctm);
	if (lt == -1)
		return G_MAXLONG;
	gt = mktime (gmttm);
	if (gt == -1)
		return G_MAXLONG;

	glong off;
	off = lt - gt;
	if ((off >= 24 * 3600) || (off <= - 24 * 3600))
		return G_MAXLONG;
	else
		return off;
}
