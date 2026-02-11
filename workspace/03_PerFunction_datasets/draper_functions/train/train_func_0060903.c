open_dir(const char *path, dirhandle *dh)
{
#if defined O_NOATIME && defined HAVE_FDOPENDIR


    int fd;

    fd = open(path, O_RDONLY | O_NONBLOCK | O_NOCTTY | O_LARGEFILE |
	      O_NOATIME | O_DIRECTORY);
    if (fd < 0) {


	if (errno == EPERM)
	    fd = open(path, O_RDONLY | O_NONBLOCK | O_NOCTTY |
		      O_LARGEFILE | O_DIRECTORY);
	if (fd < 0)
	    return -1;
    }

    *dh = fdopendir(fd);
#else
    *dh = opendir(path);
#endif

    if (!*dh)
	return -1;
    return 0;
}
