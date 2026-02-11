isdn_tty_chars_in_buffer(struct tty_struct *tty)
{
	modem_info *info = (modem_info *) tty->driver_data;

	if (isdn_tty_paranoia_check(info, tty->name, "isdn_tty_chars_in_buffer"))
		return 0;
	if (!info->online)
		return 0;
	return (info->xmit_count);
}
