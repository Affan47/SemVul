pipe_fopen(gx_io_device * iodev, const char *fname, const char *access,
           FILE ** pfile, char *rfname, uint rnamelen)
{
    errno = 0;


    if (strchr(access, '+'))
        return_error(gs_error_invalidfileaccess);


    *pfile = popen((char *)fname, (char *)access);
    if (*pfile == NULL)
        return_error(gs_fopen_errno_to_code(errno));
    if (rfname != NULL)
        strcpy(rfname, fname);
    return 0;
}
