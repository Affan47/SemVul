gid2group_utoa(long gid)
{
	char *name = gid2group(gid);
	return (name) ? name : utoa(gid);
}
