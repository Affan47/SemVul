ftp_lite_list( struct ftp_lite_server *s, const char *dir )
{
	char buffer[FTP_LITE_LINE_MAX];
	FILE *data;

	sprintf(buffer,"NLST %s",dir);

	data = ftp_lite_xfer_setup(s,buffer);
	if(data) {
		return data;
	} else {
		return 0;
	}
}
