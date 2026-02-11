open_exclusive(char *filename, mode_t mode)
{
#if defined(O_EXCL)&&defined(O_CREAT)&&defined(O_WRONLY)&&defined(O_TRUNC)


    int fd;
    (void) unlink(filename);
    fd = open(filename, O_EXCL|O_CREAT|O_WRONLY|O_TRUNC
#ifdef O_BINARY
                            |O_BINARY
#endif
#ifdef __VMS
            , mode, "ctxt=bin", "shr=nil"
#else
            , mode
#endif
          );
    if (fd < 0)
        return NULL;
    return fdopen(fd, "wb");
#else

    return fopen(filename, "wb");
#endif
}
