ftpWriteCommand(const char *buf, FtpStateData * ftpState)
{
    char *ebuf;
    debug(9, 5) ("ftpWriteCommand: %s\n", buf);
    if (Config.Ftp.telnet)
	ebuf = escapeIAC(buf);
    else
	ebuf = xstrdup(buf);
    safe_free(ftpState->ctrl.last_command);
    safe_free(ftpState->ctrl.last_reply);
    ftpState->ctrl.last_command = xstrdup(buf);
    comm_write(ftpState->ctrl.fd,
	ebuf,
	strlen(ebuf),
	ftpWriteCommandCallback,
	ftpState,
	xfree);
    ftpScheduleReadControlReply(ftpState, 0);
}
