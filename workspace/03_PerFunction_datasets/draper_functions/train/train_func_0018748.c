xconnect_ftpdata(void)
{
	char *buf_ptr;
	unsigned port_num;


	if (ftpcmd("PASV", NULL) != 227) {
		ftp_die("PASV");
	}


	buf_ptr = strrchr(buf, ')');
	if (buf_ptr) *buf_ptr = '\0';

	buf_ptr = strrchr(buf, ',');
	*buf_ptr = '\0';
	port_num = xatoul_range(buf_ptr + 1, 0, 255);

	buf_ptr = strrchr(buf, ',');
	*buf_ptr = '\0';
	port_num += xatoul_range(buf_ptr + 1, 0, 255) * 256;

	set_nport(lsa, htons(port_num));
	return xconnect_stream(lsa);
}
