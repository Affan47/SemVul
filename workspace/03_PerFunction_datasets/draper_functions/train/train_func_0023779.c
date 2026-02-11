st_get_uart_wr_room(struct st_data_s *st_gdata)
{
	struct tty_struct *tty;
	if (unlikely(st_gdata == NULL || st_gdata->tty == NULL)) {
		pr_err("tty unavailable to perform write");
		return -1;
	}
	tty = st_gdata->tty;
	return tty->ops->write_room(tty);
}
