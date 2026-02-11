vty_read_file(FILE *confp)
{
	int ret;
	vty_t *vty;

	vty = vty_new();
	vty->fd = 0;
	vty->type = VTY_TERM;
	vty->node = CONFIG_NODE;


	ret = config_from_file(vty, confp);

	if (!((ret == CMD_SUCCESS) || (ret == CMD_ERR_NOTHING_TODO))) {
		switch (ret) {
		case CMD_ERR_AMBIGUOUS:
			log_message(LOG_ERR, "Ambiguous command.\n");
			break;
		case CMD_ERR_NO_MATCH:
			log_message(LOG_ERR, "There is no such command.\n");
			break;
		}
		log_message(LOG_ERR, "Error occured during reading below line.\n%s\n"
				   , vty->buf);
		vty_close(vty);
		return -1;
	}

	vty_close(vty);
	return 0;
}
