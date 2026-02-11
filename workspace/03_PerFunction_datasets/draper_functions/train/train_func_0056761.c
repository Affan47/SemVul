ce_page_entry_to_mac (GtkEntry *entry, int type, gboolean *invalid)
{
	const char *temp, *sp;
	char *buf = NULL;
	GByteArray *mac;

	g_return_val_if_fail (entry != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ENTRY (entry), NULL);

	if (invalid)
		g_return_val_if_fail (*invalid == FALSE, NULL);

	temp = gtk_entry_get_text (entry);
	if (!temp || !strlen (temp))
		return NULL;

	sp = strchr (temp, ' ');
	if (sp)
		temp = buf = g_strndup (temp, sp - temp);

	mac = nm_utils_hwaddr_atoba (temp, type);
	g_free (buf);
	if (!mac) {
		if (invalid)
			*invalid = TRUE;
		return NULL;
	}

	if (type == ARPHRD_ETHER && !utils_ether_addr_valid ((struct ether_addr *)mac->data)) {
		g_byte_array_free (mac, TRUE);
		if (invalid)
			*invalid = TRUE;
		return NULL;
	}

	return mac;
}
