list__process_line (char     *line,
		    gpointer  data)
{
	FrCommand     *comm = FR_COMMAND (data);
	FrCommandArj  *arj_comm = FR_COMMAND_ARJ (comm);

	g_return_if_fail (line != NULL);

	if (! arj_comm->list_started) {
		if (strncmp (line, "--------", 8) == 0) {
			arj_comm->list_started = TRUE;
			arj_comm->line_no = 1;
		}
		return;
	}

	if (strncmp (line, "--------", 8) == 0) {
		arj_comm->list_started = FALSE;
		return;
	}

	if (g_regex_match (arj_comm->filename_line_regex, line, 0, NULL)) {
		FileData   *fdata;
		const char *name_field;

		arj_comm->line_no = 1;

		arj_comm->fdata = fdata = file_data_new ();

		name_field = _g_str_get_last_field (line, 2);

		if (*name_field == '/') {
			fdata->full_path = g_strdup (name_field);
			fdata->original_path = fdata->full_path;
		}
		else {
			fdata->full_path = g_strconcat ("/", name_field, NULL);
			fdata->original_path = fdata->full_path + 1;
		}

		fdata->link = NULL;

		fdata->name = g_strdup (_g_path_get_basename (fdata->full_path));
		fdata->path = _g_path_remove_level (fdata->full_path);
	}
	else if (arj_comm->line_no == 2) {
		FileData  *fdata;
		char     **fields;

		fdata = arj_comm->fdata;


		fields = _g_str_split_line (line, 10);
		fdata->size = g_ascii_strtoull (fields[2], NULL, 10);
		fdata->modified = mktime_from_string (fields[5], fields[6]);
		if ((strcmp (fields[1], "MS-DOS") == 0) || (strcmp (fields[1], "WIN32") == 0))
			fdata->encrypted = (g_ascii_strcasecmp (fields[7], "11") == 0);
		else
			fdata->encrypted = (g_ascii_strcasecmp (fields[9], "11") == 0);
		g_strfreev (fields);

		if (*fdata->name == 0)
			file_data_free (fdata);
		else
			fr_archive_add_file (FR_ARCHIVE (comm), fdata);
		arj_comm->fdata = NULL;
	}

	arj_comm->line_no++;
}
