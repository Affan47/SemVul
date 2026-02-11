parse_template (GFile *file)
{
	GList  *result = NULL;
	GError *error = NULL;

	yy_parsed_doc = NULL;
	yy_istream = g_file_read (file, NULL, &error);
	if (error == NULL) {
		if (gth_albumtheme_yyparse () == 0)
			result = yy_parsed_doc;
		else
			debug (DEBUG_INFO, "<<syntax error>>");

		g_input_stream_close (G_INPUT_STREAM (yy_istream), NULL, &error);
		g_object_unref (yy_istream);
	}
	else {
		g_warning ("%s", error->message);
		g_clear_error (&error);
	}

	return result;
}
