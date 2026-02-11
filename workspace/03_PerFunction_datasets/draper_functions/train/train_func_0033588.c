ftpTimeout(int fd, void *data)
{
    FtpStateData *ftpState = data;
    StoreEntry *entry = ftpState->entry;
    debug(9, 4) ("ftpTimeout: FD %d: '%s'\n", fd, storeUrl(entry));
    if (SENT_PASV == ftpState->state && fd == ftpState->data.fd) {

	ftpState->fwd->flags.dont_retry = 0;
	ftpState->fwd->flags.ftp_pasv_failed = 1;
	debug(9, 1) ("ftpTimeout: timeout in SENT_PASV state\n");
    }
    ftpFailed(ftpState, ERR_READ_TIMEOUT);

}
