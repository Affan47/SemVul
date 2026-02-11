httpgetcwd(uh, path, size)
int uh;
char *path;
ALLOC_T size;
{
	int n, flags;

	if (!(urlhostlist[uh].http)) {
		errno = EINVAL;
		return(NULL);
	}
	flags = (UGP_SCHEME | UGP_HOST | UGP_CWD);
	if (urlhostlist[uh].type == TYPE_FTP) flags |= UGP_USER;
	n = urlgenpath(uh, path, size, flags);
	if (n < 0) return(NULL);

	return(path);
}
