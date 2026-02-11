gdb_getc(struct gdb_data *data)
{
	int c;


	if (data->head == data->tail && gdb_read(data, 1) < 0)
		return -1;

	c = data->xbuf[data->head];
	data->head++;

	return c;
}
