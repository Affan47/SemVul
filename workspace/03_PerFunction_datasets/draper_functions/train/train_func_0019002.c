ftp_lite_rename( struct ftp_lite_server *s, const char *oldname, const char *newname )
{
	char buffer[FTP_LITE_LINE_MAX];
	int r1, r2;

	ftp_lite_send_command(s,"RNFR %s",oldname);
	ftp_lite_send_command(s,"RNTO %s",newname);

	r1 = ftp_lite_get_response(s,0,buffer);
	r2 = ftp_lite_get_response(s,0,buffer);

	if( r1/100 != 3 ) {
		errno = ftp_lite_error(r1);
		return 0;
	}

	if( r2/100 != 2 ) {
		errno = ftp_lite_error(r2);
		return 0;
	}

	return 1;
}
