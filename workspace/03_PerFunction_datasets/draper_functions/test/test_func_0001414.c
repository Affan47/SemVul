build_old_prefix(aClient *orig, char *imsg, aClient *dest,
	char *dname)
{
	if (oldplen != 0)
	{
		return;
	}
	if (dname == NULL)
	{
		dname = dest->name;
	}
	oldplen = sprintf(oldprefixbuf, ":%s %s %s", orig->name, imsg, dname);
	if (oldplen > maxplen)
	{
		maxplen = oldplen;
	}
}
