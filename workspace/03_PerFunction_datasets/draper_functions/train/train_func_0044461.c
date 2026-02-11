client_scan(const char *file, int scantype, int *infected, int *err, int maxlevel, int session, int flags) {
    int ret;
    char *fullpath = makeabs(file);

    if(!fullpath)
	return 0;
    if (!session)
	ret = serial_client_scan(fullpath, scantype, infected, err, maxlevel, flags);
    else
	ret = parallel_client_scan(fullpath, scantype, infected, err, maxlevel, flags);
    free(fullpath);
    return ret;
}
