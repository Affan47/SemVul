CAlistopen(FILE *FromServer, FILE *ToServer, const char *request)
{
    int fd, oerrno;


    if (FromServer == NULL || ToServer == NULL) {
	errno = EBADF;
	return NULL;
    }

    CApathname = concatpath(innconf->pathtmp, INN_PATH_TEMPACTIVE);
    fd = mkstemp(CApathname);
    if (fd < 0) {
        oerrno = errno;
        free(CApathname);
        CApathname = 0;
        errno = oerrno;
        return NULL;
    }
    close(fd);
    return CAfp = CA_listopen(CApathname, FromServer, ToServer, request);
}
