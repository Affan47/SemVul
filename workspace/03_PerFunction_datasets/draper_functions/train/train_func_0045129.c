set_console_loglevel(int exiting) {
	if (!printk_f)
		return;
	fseek(printk_f, 0, SEEK_SET);
	fprintf(printk_f, "%d\n", console_loglevel);


	send_message(USERUI_MSG_SET_LOGLEVEL, (void *) &console_loglevel, sizeof(console_loglevel));

	if (!exiting)
		active_ops->log_level_change();
}
