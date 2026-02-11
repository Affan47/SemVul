httpfstat(uh, stp)
int uh;
struct stat *stp;
{
	if (!(urlhostlist[uh].http)) return(seterrno(EINVAL));
	if ((urlhostlist[uh].http) -> flags & HFL_CLENGTH)
		stp -> st_size = (urlhostlist[uh].http) -> clength;
	else stp -> st_size = (off_t)-1;
	if ((urlhostlist[uh].http) -> flags & HFL_MTIME)
		stp -> st_mtime = (urlhostlist[uh].http) -> mtim;

	return(0);
}
