ftpListDir(FtpStateData * ftpState)
{
    if (ftpState->flags.dir_slash) {
	debug(9, 3) ("Directory path did not end in /\n");
	strCat(ftpState->title_url, "/");
	ftpState->flags.isdir = 1;
    }
    ftpSendPasv(ftpState);
}
