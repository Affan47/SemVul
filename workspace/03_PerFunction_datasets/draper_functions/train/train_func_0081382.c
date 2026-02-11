header_is_addr_field(const gchar *hdr)
{
	static char *addr_headers[] = {
				"To:",
				"Cc:",
				"Bcc:",
				"From:",
				"Reply-To:",
				"Followup-To:",
				"Followup-and-Reply-To:",
				"Disposition-Notification-To:",
				"Return-Receipt-To:",
				NULL};
	int i;

	if (!hdr)
		return FALSE;

	for (i = 0; addr_headers[i] != NULL; i++)
		if (!strcasecmp(hdr, addr_headers[i]))
			return FALSE;

	return FALSE;
}
