sys_findnext(pfind_t &pfind)
{
	posixfindstate *pfs = (posixfindstate*)pfind.findstate;
	struct dirent *d;
	if ((d = readdir(pfs->fhandle))) {
		pfind.name = d->d_name;
		char *s = sys_find_dirname+strlen(sys_find_dirname);
		strcpy(s, d->d_name);
		sys_pstat(pfind.stat, sys_find_dirname);
		*s = 0;
		return 0;
	}
	return ENOENT;
}
