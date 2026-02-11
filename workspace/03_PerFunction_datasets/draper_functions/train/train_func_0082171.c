sep_by_tag(gchar *line, gchar *tag, gchar *filename, gint lineno) {
	gint tag_len;
	gchar *ret;

	tag_len = strlen(tag);

	ret = line + tag_len;

	crop_by_whitespace(ret);

	if(!*ret) {
		gui_warning(_("Line %d of %s contains the tag '%s' without a value"), lineno, filename, tag);
		return FALSE;
	} else {
		return ret;
	}
}
