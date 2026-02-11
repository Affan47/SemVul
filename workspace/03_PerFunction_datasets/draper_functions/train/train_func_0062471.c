procmime_get_tmp_file_name(MimeInfo *mimeinfo)
{
	static guint32 id = 0;
	gchar *base;
	gchar *filename;
	gchar f_prefix[10];

	cm_return_val_if_fail(mimeinfo != NULL, NULL);

	g_snprintf(f_prefix, sizeof(f_prefix), "%08x.", id++);

	if ((mimeinfo->type == MIMETYPE_TEXT) && !g_ascii_strcasecmp(mimeinfo->subtype, "html"))
		base = g_strdup("mimetmp.html");
	else {
		const gchar *basetmp;

		basetmp = procmime_mimeinfo_get_parameter(mimeinfo, "filename");
		if (basetmp == NULL)
			basetmp = procmime_mimeinfo_get_parameter(mimeinfo, "name");
		if (basetmp == NULL)
			basetmp = "mimetmp";
		basetmp = g_path_get_basename(basetmp);
		if (*basetmp == '\0')
			basetmp = g_strdup("mimetmp");
		base = conv_filename_from_utf8(basetmp);
		g_free((gchar*)basetmp);
		subst_for_shellsafe_filename(base);
	}

	filename = g_strconcat(get_mime_tmp_dir(), G_DIR_SEPARATOR_S,
			       f_prefix, base, NULL);

	g_free(base);

	return filename;
}
