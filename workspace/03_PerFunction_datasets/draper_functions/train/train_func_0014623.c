workbook_sheet_add (Workbook *wb, int pos, int columns, int rows)
{
	char *name = workbook_sheet_get_free_name (wb, _("Sheet"), TRUE, FALSE);
	Sheet *new_sheet = sheet_new (wb, name, columns, rows);
	g_free (name);

	if (pos == -1)
		pos = wb->sheets->len;
	workbook_sheet_attach_at_pos (wb, new_sheet, pos);


	g_signal_emit (G_OBJECT (wb), signals [SHEET_ADDED], 0);

	g_object_unref (new_sheet);

	return new_sheet;
}
