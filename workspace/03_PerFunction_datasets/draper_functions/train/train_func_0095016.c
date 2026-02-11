st_tty_receive(struct tty_struct *tty, const unsigned char *data,
			   char *tty_flags, int count)
{
#ifdef VERBOSE
	print_hex_dump(KERN_DEBUG, ">in>", DUMP_PREFIX_NONE,
		16, 1, data, count, 0);
#endif


	st_recv(tty->disc_data, data, count);
	pr_debug("done %s", __func__);
}
