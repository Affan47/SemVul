pty_write_room(struct tty_struct *tty)
{
	if (tty->stopped)
		return 0;
	return tty_buffer_space_avail(tty->link->port);
}
