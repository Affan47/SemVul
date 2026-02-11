ximSyncReplyProc(conn, major, minor, arglen)
IMConnection *conn;
int major;
int minor;
int arglen;
{
    IMIC *icp;

    TRACE(("ximSyncReplyProc(#%d)\n", conn->serial));

    if ((icp = IMGetIC(conn, arglen)) == NULL) return;
    if (arglen != 4) {
	DPRINT(("ximSyncReplyProc: arglen != 4\n"));
	return;
    }
    if (icp->state & IC_SYNCING) {
	icp->state &= ~IC_SYNCING;
	processPendingEvents(icp, icp->pending_events);
    }
}
