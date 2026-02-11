ftpopen(uh, path, flags)
int uh;
CONST char *path;
int flags;
{
	int cmd;

	switch (flags & O_ACCMODE) {
		case O_RDONLY:
			cmd = FTP_RETR;
			break;
		case O_WRONLY:
			cmd = FTP_STOR;
			break;
		default:
			return(seterrno(EACCES));

			break;
	}

	return(ftpopenport(uh, cmd, path, FTP_IMAGE));
}
