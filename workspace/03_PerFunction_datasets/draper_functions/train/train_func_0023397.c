want_interactive(void)
{
	char c;
	static bool gotinteractive;
	static bool interactive;

	if (rc_yesno(getenv("EINFO_QUIET")))
		return false;
	if (!gotinteractive) {
		gotinteractive = true;
		interactive = rc_conf_yesno("rc_interactive");
	}
	if (!interactive)
		return false;
	c = read_key(false);
	return (c == 'I' || c == 'i') ? true : false;
}
