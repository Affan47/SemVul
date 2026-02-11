keypress_signal_handler(int sig) {
	static char next_is_escaped = 0;
	unsigned char a, b;

	while (1) {
		if (next_is_escaped) {
			if (read(STDIN_FILENO, &b, 1) <= 0)
				break;
			else {
				if (!raw_keypresses)
					a = ascii_to_raw(a);
				next_is_escaped = 0;
				if (running)
				    active_ops->keypress((a << 8)|b);
			}
		} else {
			if (read(STDIN_FILENO, &a, 1) <= 0)
				break;
			else {
				if (!raw_keypresses)
					a = ascii_to_raw(a);
				if (a == 0xe0) {
					next_is_escaped = 1;
					continue;
				}
				if (running)
				    active_ops->keypress((a << 8)|b);
				active_ops->keypress(a);
			}
		}
	}
}
