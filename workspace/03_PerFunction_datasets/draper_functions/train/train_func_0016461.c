netsys_posix_openpt(value noctty)
{
#ifdef HAVE_PTY
    int fd;
    int flags;

    flags = O_RDWR;
    if (Bool_val(noctty) != 0) flags |= O_NOCTTY;

#ifdef HAVE_PTY_OPENPT
    fd = posix_openpt(flags);
#else
    fd = open("/dev/ptmx", flags);
#endif

    if (fd == -1) uerror("openpt", Nothing);
    return Val_int(fd);
#else
    invalid_argument("Netsys_posix.posix_openpt not available");
#endif
}
