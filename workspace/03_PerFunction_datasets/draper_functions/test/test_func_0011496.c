get_uncompressed_name_from_archive (FrCommand  *comm,
				    const char *archive)
{
	GFile        *file;
	GInputStream *stream;
	char         *filename = NULL;

	if (! _g_mime_type_matches (FR_ARCHIVE (comm)->mime_type, "application/x-gzip"))
		return NULL;

	file = g_file_new_for_path (archive);

	stream = (GInputStream *) g_file_read (file, NULL, NULL);
	if (stream != NULL) {
		gboolean filename_present = TRUE;
		char     buffer[10];

		if (g_input_stream_read (stream, buffer, 10, NULL, NULL) >= 0) {

			if (((unsigned char)(buffer[3]) & 0x08) != 0x08)
				filename_present = FALSE;


			if (((unsigned char)(buffer[3]) & 0x04) == 0x04)
				filename_present = FALSE;
		}

		if (filename_present) {
			GString *str = NULL;

			str = g_string_new ("");
			while (g_input_stream_read (stream, buffer, 1, NULL, NULL) > 0) {
				if (buffer[0] == '\0') {
					filename = g_strdup (_g_path_get_basename (str->str));
#ifdef DEBUG
					g_message ("filename is: %s", filename);
#endif
					break;
				}
				g_string_append_c (str, buffer[0]);
			}
			g_string_free (str, TRUE);
		}
		g_object_unref (stream);
	}
	g_object_unref (file);

	return filename;
}
