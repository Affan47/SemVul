DXLExitDX(DXLConnection *conn)
{
    int retval;
    int sts;
    fd_set fds;
#ifdef hp700
    int width = MAXFUPLIM;
#else
#ifdef aviion
    int width = NOFILE;
#else
#ifdef solaris
    int width = FD_SETSIZE;
#else
#ifdef  DXD_HAS_WINSOCKETS
    int width = FD_SETSIZE;
#else
#ifndef OS2
    int width = getdtablesize();
#endif
#endif
#endif
#endif
#endif
    const char *cmd;

    if (conn->fd <= 0 )
	return ERROR;

    if (conn->dxuiConnected)
	cmd = "exit";
    else
	cmd = "quit;\n";


    DXLSetSynchronization(conn,0);

    sts = DXLSend(conn, cmd);

    FD_ZERO(&fds);
    FD_SET(conn->fd, &fds);
#ifdef DXD_HAS_WINSOCKETS
    select(width, &fds, NULL, NULL, NULL);
#else
#ifndef OS2

    SELECT_INTR(width, (SELECT_ARG_TYPE *)&fds, NULL, NULL, NULL, retval);
#else
    select(&conn->fd, 1, 0, 0, -1);
#endif
#endif

    DXLCloseConnection(conn);

    return sts;
}
