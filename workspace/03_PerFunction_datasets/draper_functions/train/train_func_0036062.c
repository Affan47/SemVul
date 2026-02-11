xgetcwd()
{
    char *result;
    char *cwd;

    errno = 0;

#ifdef HAVE_GETCWD
    {
	size_t size;

	cwd = xmalloc(size = 64);

	while ((result = getcwd(cwd, size)) == NULL && errno == ERANGE)
	{
	    cwd = xrealloc(cwd, size += 64);
	    errno = 0;
	}
    }
#else
    {


	cwd    = xmalloc(MAXPATHSIZE + 2);
	result = getwd(cwd);

	if (result)
	    cwd = xrealloc(cwd, strlen(cwd) + 1);
    }
#endif

    if (result == NULL)
    {
	xfree(cwd);
	return NULL;
    }

    return cwd;
}
