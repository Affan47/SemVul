excel_file_probe (GOFileOpener const *fo, GsfInput *input, GOFileProbeLevel pl)
{
	GsfInfile *ole;
	GsfInput  *stream;
	gboolean res = FALSE;

	if (input == NULL)
		return FALSE;
	ole = gsf_infile_msole_new (input, NULL);
	if (ole == NULL) {
		guint8 const *data;
		gsf_input_seek (input, 0, G_SEEK_SET);
		data = gsf_input_read (input, 2, NULL);
		return data && data[0] == 0x09 && (data[1] & 0xf1) == 0;
	}

	stream = find_content_stream (ole, NULL);
	if (stream != NULL) {
		g_object_unref (stream);
		res = TRUE;
	}
	g_object_unref (ole);

	return res;
}
