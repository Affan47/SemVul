process_line (char     *line,
	      gpointer  data)
{
	FileData    *fdata;
	FrCommand   *comm = FR_COMMAND (data);
	char       **fields;
	int          date_idx;
	char        *field_month, *field_day, *field_time, *field_year;
	char        *field_size, *field_name;

	g_return_if_fail (line != NULL);

	fdata = file_data_new ();

	date_idx = _g_line_get_index_from_pattern (line, "%c%c%c %a%n %n%n:%n%n %n%n%n%n");

	field_size = _g_line_get_prev_field (line, date_idx, 1);
	fdata->size = g_ascii_strtoull (field_size, NULL, 10);
	g_free (field_size);

	field_month = _g_line_get_next_field (line, date_idx, 1);
	field_day = _g_line_get_next_field (line, date_idx, 2);
	field_time = _g_line_get_next_field (line, date_idx, 3);
	field_year = _g_line_get_next_field (line, date_idx, 4);
	fdata->modified = mktime_from_string (field_time, field_day, field_month, field_year);
	g_free (field_day);
	g_free (field_month);
	g_free (field_year);
	g_free (field_time);


	field_name = ar_get_last_field (line, date_idx, 5);

	fields = g_strsplit (field_name, " -> ", 2);

	if (fields[0] == NULL) {
		g_strfreev (fields);
		g_free (field_name);
		file_data_free (fdata);
		return;
	}

	if (fields[1] == NULL) {
		g_strfreev (fields);
		fields = g_strsplit (field_name, " link to ", 2);
	}

	if (*(fields[0]) == '/') {
		fdata->full_path = g_strdup (fields[0]);
		fdata->original_path = fdata->full_path;
	} else {
		fdata->full_path = g_strconcat ("/", fields[0], NULL);
		fdata->original_path = fdata->full_path + 1;
	}

	if (fields[1] != NULL)
		fdata->link = g_strdup (fields[1]);
	g_strfreev (fields);
	g_free (field_name);

	fdata->name = g_strdup (_g_path_get_basename (fdata->full_path));
	fdata->path = _g_path_remove_level (fdata->full_path);

	if (*fdata->name == 0)
		file_data_free (fdata);
	else
		fr_archive_add_file (FR_ARCHIVE (comm), fdata);
}
