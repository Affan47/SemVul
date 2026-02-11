netsnmp_sock_buffer_set(int s, int optname, int local, int size)
{
#if ! defined(SO_SNDBUF) && ! defined(SO_RCVBUF)
    DEBUGMSGTL(("socket:buffer", "Changing socket buffer is not supported\n"));
    return -1;
#else
    const char     *buftype;
    int            curbuf = 0;
    socklen_t      curbuflen = sizeof(int);

#   ifndef  SO_SNDBUF
    if (SO_SNDBUF == optname) {
        DEBUGMSGTL(("socket:buffer",
                    "Changing socket send buffer is not supported\n"));
        return -1;
    }
#   endif
#   ifndef  SO_RCVBUF
    if (SO_RCVBUF == optname) {
        DEBUGMSGTL(("socket:buffer",
                    "Changing socket receive buffer is not supported\n"));
        return -1;
    }
#   endif


    if (0 == size)
        size = _sock_buffer_size_get(optname, local, &buftype);
    else {
        buftype = _sock_buf_type_get(optname, local);
        DEBUGMSGT(("verbose:socket:buffer", "Requested %s is %d\n",
                   buftype, size));
    }

    if ((getsockopt(s, SOL_SOCKET, optname, (void *) &curbuf,
                    &curbuflen) == 0)
        && (curbuflen == sizeof(int))) {

        DEBUGMSGT(("verbose:socket:buffer", "Original %s is %d\n",
                   buftype, curbuf));
        if (curbuf >= size) {
            DEBUGMSGT(("verbose:socket:buffer",
                      "New %s size is smaller than original!\n", buftype));
        }
    }


    if (size <= 0) {
       DEBUGMSGT(("socket:buffer",
                    "%s not valid or not specified; using OS default(%d)\n",
                    buftype,curbuf));
       return curbuf;
    }


    if (setsockopt(s, SOL_SOCKET, optname, (void *) &size, sizeof(int)) == 0) {


        DEBUGIF("socket:buffer") {
            DEBUGMSGT(("socket:buffer", "Set %s to %d\n",
                       buftype, size));
            if ((getsockopt(s, SOL_SOCKET, optname, (void *) &curbuf,
                            &curbuflen) == 0)
                    && (curbuflen == sizeof(int))) {

                DEBUGMSGT(("verbose:socket:buffer",
                           "Now %s is %d\n", buftype, curbuf));
            }
        }


        if (curbuf < size) {
            curbuf = _sock_buffer_maximize(s, optname, buftype, size);
            if(-1 != curbuf)
                size = curbuf;
        }

    } else {


        DEBUGMSGTL(("socket:buffer", "couldn't set %s to %d\n",
                    buftype, size));

        curbuf = _sock_buffer_maximize(s, optname, buftype, size);
        if(-1 != curbuf)
            size = curbuf;
    }

    return size;
#endif
}
