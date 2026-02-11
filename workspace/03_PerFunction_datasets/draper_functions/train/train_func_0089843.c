rb_io_fmode_oflags(int fmode)
{
    int oflags = 0;

    switch (fmode & FMODE_READWRITE) {
      case FMODE_READABLE:
        oflags |= O_RDONLY;
        break;
      case FMODE_WRITABLE:
        oflags |= O_WRONLY;
        break;
      case FMODE_READWRITE:
        oflags |= O_RDWR;
        break;
    }

    if (fmode & FMODE_APPEND) {
        oflags |= O_APPEND;
    }
    if (fmode & FMODE_TRUNC) {
        oflags |= O_TRUNC;
    }
    if (fmode & FMODE_CREATE) {
        oflags |= O_CREAT;
    }
#ifdef O_BINARY
    if (fmode & FMODE_BINMODE) {
        oflags |= O_BINARY;
    }
#endif

    return oflags;
}
