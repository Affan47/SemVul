create_link(char *pfilename,
	    const char *linkname, mode_t linktype,
	    const char *prevlinkname)
{
    struct stat		stat_buf;

    if (stat(prevlinkname, &stat_buf) == 0)
    {
	unlink(prevlinkname);
    }
    if (stat(linkname, &stat_buf) == 0)
    {
	if (prevlinkname) {
	    rename(linkname, prevlinkname);
	}
	else {
	    unlink(linkname);
	}
    }
#ifndef _WIN32
    if (linktype == S_IFLNK)
    {
	symlink(pfilename, linkname);
    }
    else
    {
	link(pfilename, linkname);
    }
#else
    fprintf(stderr, "Creating link from %s to %s not supported", pfilename, linkname);
#endif
}
