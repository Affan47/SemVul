utils_mark(const char *file, gint line, gboolean mark, gint marker)
{
	if (line)
	{
		GeanyDocument *doc = document_find_by_real_path(file);

		if (doc)
		{
			if (mark)
				sci_set_marker_at_line(doc->editor->sci, line - 1, marker);
			else
				sci_delete_marker_at_line(doc->editor->sci, line - 1, marker);
		}
	}
}
