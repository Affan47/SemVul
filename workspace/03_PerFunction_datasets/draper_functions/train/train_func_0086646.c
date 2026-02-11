disable_echo(struct termios *saved_settings)
{
	struct termios current_settings;
	int rc = 0;

	rc = tcgetattr(0, &current_settings);
	if (rc)
		return rc;
	*saved_settings = current_settings;
	current_settings.c_lflag &= ~ECHO;
	rc = tcsetattr(0, TCSANOW, &current_settings);
	return rc;
}
