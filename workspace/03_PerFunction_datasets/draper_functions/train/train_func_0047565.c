skype_send_raw(PurpleConnection *gc, const char *buf, int len)
{
	gchar *newbuf = NULL;
	int newlen = 0;

	newbuf = g_strndup(buf, len);
	newlen = strlen(newbuf);
	if (newbuf != NULL)
	{
		skype_send_message_nowait(newbuf);
		g_free(newbuf);
	}

	return newlen;
}
