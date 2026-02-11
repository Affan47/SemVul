gm_default_charset() {
	static const gchar *loc = NULL;

	if (loc == NULL) {
		g_get_charset(&loc);
	}

	if (loc == NULL || *loc == 0) {
		loc = "ISO-8859-15";
	}

	return loc;
}
