errmsg(int e, int action)
{
	if (e != ENOENT && e != ENOTDIR)
		return strerror(e);

	if (action & E_OPEN)
		return "No such file";
	else if (action & E_CREAT)
		return "Directory nonexistent";
	else
		return "not found";
}
