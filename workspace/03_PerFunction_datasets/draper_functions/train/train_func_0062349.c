JimMakeChannel(Jim_Interp *interp, FILE *fh, int fd, Jim_Obj *filename,
    const char *hdlfmt, int family, const char *mode)
{
    AioFile *af;
    char buf[AIO_CMD_LEN];
    int OpenFlags = 0;

    if (filename == NULL) {
        filename = Jim_NewStringObj(interp, hdlfmt, -1);
    }

    Jim_IncrRefCount(filename);

    if (fh == NULL) {
        if (fd < 0) {
            fh = fopen(Jim_String(filename), mode);
        }
        else {
            fh = fdopen(fd, mode);
        }
    }
    else {
        OpenFlags = AIO_KEEPOPEN;
    }

    if (fh == NULL) {
        JimAioSetError(interp, filename);
#if !defined(JIM_ANSIC)
        if (fd >= 0) {
            close(fd);
        }
#endif
        Jim_DecrRefCount(interp, filename);
        return JIM_ERR;
    }


    af = Jim_Alloc(sizeof(*af));
    memset(af, 0, sizeof(*af));
    af->fp = fh;
    af->fd = fileno(fh);
    af->filename = filename;
#ifdef FD_CLOEXEC
    if ((OpenFlags & AIO_KEEPOPEN) == 0) {
        fcntl(af->fd, F_SETFD, FD_CLOEXEC);
    }
#endif
    af->OpenFlags = OpenFlags;
#ifdef O_NDELAY
    af->flags = fcntl(af->fd, F_GETFL);
#endif
    af->addr_family = family;
    snprintf(buf, sizeof(buf), hdlfmt, Jim_GetId(interp));
    Jim_CreateCommand(interp, buf, JimAioSubCmdProc, af, JimAioDelProc);

    Jim_SetResultString(interp, buf, -1);

    return JIM_OK;
}
