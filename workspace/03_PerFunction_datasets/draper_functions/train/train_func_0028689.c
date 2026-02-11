writeWepKey(int network_id, QLineEdit *edit, int id)
{
	char buf[10];
	bool hex;
	const char *txt, *pos;
	size_t len;

	if (!edit->isEnabled() || edit->text().isEmpty())
		return;


	txt = edit->text().toAscii().constData();
	if (strcmp(txt, WPA_GUI_KEY_DATA) == 0)
		return;
	len = strlen(txt);
	if (len == 0)
		return;
	pos = txt;
	hex = true;
	while (*pos) {
		if (!((*pos >= '0' && *pos <= '9') ||
		      (*pos >= 'a' && *pos <= 'f') ||
		      (*pos >= 'A' && *pos <= 'F'))) {
			hex = false;
			break;
		}
		pos++;
	}
	if (hex && len != 10 && len != 26 && len != 32)
		hex = false;
	snprintf(buf, sizeof(buf), "wep_key%d", id);
	setNetworkParam(network_id, buf, txt, !hex);
}
