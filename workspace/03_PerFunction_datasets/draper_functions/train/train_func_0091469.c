IsMemberOf (gid_t user, struct group *g)
{
	if (!g)
		return FALSE;


	if (IsDefaultGroup (user, g->gr_gid))
		return TRUE;


	return IsMemberInList (user, g);
}
