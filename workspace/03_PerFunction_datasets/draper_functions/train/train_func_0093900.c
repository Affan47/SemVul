set_speed_or_die(enum speed_setting type, const char *arg,
					struct termios *mode)
{
	speed_t baud;

	baud = tty_value_to_baud(xatou(arg));

	if (type != output_speed) {
		cfsetispeed(mode, baud);
	}
	if (type != input_speed) {
		cfsetospeed(mode, baud);
	}
}
