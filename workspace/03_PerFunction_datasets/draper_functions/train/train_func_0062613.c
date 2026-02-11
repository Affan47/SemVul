pendingClose(fdInfoType *info,int why)
{
    register connInfoType *conn=info->conn;

    if (info->conn) {
	if (info->flags&FD_IS_LISTEN) {
	    syslog(LOG_WARNING,"pendingClose(listen socket,%d)",why);
#ifdef __hpux
	    dumpMap(0);
#endif
	    unListen(1);
	    return;
	}
	pendingCloses++;
	conn->flags|=CO_CLOSE_PENDING;
	conn->error=why;
    } else {
	closeConnection(info,why,1);
    }
}
