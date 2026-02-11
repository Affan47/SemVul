ekg_recode_to_locale_dup(enum ekg_recode_name enc, const char *buf) {
	struct ekg_recoder *rec;

	if (!buf)
		return NULL;

	rec = ekg_recode_get(enc);
	if (rec->recode_to_locale)
		return rec->recode_to_locale(rec, 1, (char *) buf);

	return xstrdup(buf);
}
