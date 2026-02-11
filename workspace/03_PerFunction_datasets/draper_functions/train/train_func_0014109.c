is_known_google_im_protocol (const gchar *protocol)
{
	const gchar *known_protocols[] = {
		"AIM", "MSN", "YAHOO", "SKYPE", "QQ",
		"GOOGLE_TALK", "ICQ", "JABBER"
	};
	guint i;

	if (NULL == protocol)
		return FALSE;

	for (i = 0; i < G_N_ELEMENTS (known_protocols); i++) {
		if (0 == g_ascii_strcasecmp (known_protocols[i], protocol))
			return TRUE;
	}

	return FALSE;
}
