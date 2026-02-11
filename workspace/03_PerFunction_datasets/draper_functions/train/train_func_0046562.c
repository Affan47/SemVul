gdb_packet_end(struct gdb_data *data)
{
	int i;
	int c = 0;

	for (i = 1; i < data->outlen; i++)
		c = (c + data->outbuf[i]) & 0xff;
	gdb_printf(data, "#%02x", c);
}
