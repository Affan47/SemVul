write_(Driver * drvthis, const unsigned char *buf, size_t count)
{
	int write_count = 0, written;
	PrivateData *p = drvthis->private_data;

	while (write_count < count) {
		written = write(p->fd, &buf[write_count], count - write_count);
		if (written == -1) {
			report(RPT_ERR, "SureElec: cannot write to port");
			return -1;
		}
		write_count += written;
	}
	return write_count;
}
