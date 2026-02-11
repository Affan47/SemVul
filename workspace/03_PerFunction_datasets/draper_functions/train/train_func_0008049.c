ftpReadSize(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debug(9, 3) ("This is ftpReadSize\n");
    if (code == 213) {
	ftpUnhack(ftpState);
	ftpState->size = strto_off_t(ftpState->ctrl.last_reply, NULL, 10);
	if (ftpState->size == 0) {
	    debug(9, 2) ("ftpReadSize: SIZE reported %s on %s\n",
		ftpState->ctrl.last_reply,
		strBuf(ftpState->title_url));
	    ftpState->size = -1;
	}
    } else if (code < 0) {
	ftpFail(ftpState);
	return;
    }
    ftpSendPasv(ftpState);
}
