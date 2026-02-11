re_nick (void)
{
	static GRegex *nick_ret;
	char *grist;

	if (nick_ret) return nick_ret;

	grist = g_strdup (
		"("
			NICK
		")"
	);
	nick_ret = make_re (grist);
	return nick_ret;
}
