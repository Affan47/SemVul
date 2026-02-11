_dxl_WaitForReadable(DXLConnection *conn)
{
    int retval;
#ifndef OS2
    fd_set fds;
#endif
#ifdef hp700
    int    width = MAXFUPLIM;
#else
#ifdef aviion
    int    width = NOFILE;
#else
#ifdef solaris
    int    width = FD_SETSIZE;
#else
#ifdef DXD_HAS_WINSOCKETS
    int    width = FD_SETSIZE;
#else
#ifndef OS2
    int    width = getdtablesize();
#endif
#endif
#endif
#endif
#endif

    if (conn->fd < 0)
	return 0;

#if  !defined(OS2)  && !defined(DXD_HAS_WINSOCKETS)
    FD_ZERO(&fds);
    FD_SET(conn->fd, &fds);


	SELECT_INTR((conn->fd + 1), (SELECT_ARG_TYPE *)&fds, NULL, NULL, NULL, retval);
    if(retval < 0)
        goto error;
#endif

#ifdef OS2
    if (select(&conn->fd, 1, 0, 0, -1)<0)
        goto error;
#endif

#ifdef DXD_HAS_WINSOCKETS
    FD_ZERO(&fds);
    FD_SET(conn->fd, &fds);
	width =  select((conn->fd + 1), &fds, NULL, NULL, NULL);
    if (width < 0)
        goto error;

#endif
    return 1;

error:
   _dxl_InvalidateSocket(conn);
    return 0;
}
