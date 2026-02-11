short_command(int priv, int fd, int cmd1, int cmd2,
			 int cmd3, const char *data, void *extra_data)
{
	unsigned char cdb[6] = { 0, 0, 0, 0, 0, 0 };

	cdb[0] = cmd1;
	cdb[1] = cmd2;
	cdb[4] = cmd3;

	return zip_cmd(priv, fd, cdb, 6, SCSI_IO_WRITE,
		       (char *) data, data ? strlen(data) : 0, extra_data);
}
