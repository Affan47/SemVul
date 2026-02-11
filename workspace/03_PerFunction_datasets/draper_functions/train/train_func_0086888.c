up_device_supply_make_safe_string (gchar *text)
{
	guint i;
	guint idx = 0;


	if (text == NULL)
		return;

	if (g_utf8_validate (text, -1, NULL))
		return;


	for (i=0; text[i] != '\0'; i++) {
		if (g_ascii_isprint (text[i])) {

			if (idx != i)
				text[idx] = text[i];
			idx++;
		} else {
			g_debug ("invalid char '%c'", text[i]);
		}
	}


	text[idx] = '\0';
}
