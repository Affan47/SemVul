vty_kill_line(vty_t *vty)
{
	int i, size;

	size = vty->length - vty->cp;

	if (size == 0)
		return;

	for (i = 0; i < size; i++)
		vty_write(vty, &telnet_space_char, 1);
	for (i = 0; i < size; i++)
		vty_write(vty, &telnet_backward_char, 1);

	memset (&vty->buf[vty->cp], 0, size);
	vty->length = vty->cp;
}
