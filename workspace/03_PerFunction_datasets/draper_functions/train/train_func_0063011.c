ReturnOpen(Ns_Conn *conn, int status, char *type, Tcl_Channel chan,
	FILE *fp, int fd, off_t off, int len)
{
    int result;

    Ns_ConnSetRequiredHeaders(conn, type, len);
    Ns_ConnQueueHeaders(conn, status);
    if (chan != NULL) {
	result = Ns_ConnSendChannel(conn, chan, len);
    } else if (fp != NULL) {
	result = Ns_ConnSendFp(conn, fp, len);
    } else if (off < 0) {
	result = Ns_ConnSendFd(conn, fd, len);
    } else {
	result = Ns_ConnSendFdEx(conn, fd, off, len);
    }
    if (result == NS_OK) {
        result = Ns_ConnClose(conn);
    }
    return result;
}
