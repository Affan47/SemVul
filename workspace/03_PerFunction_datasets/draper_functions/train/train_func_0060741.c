_insert (ECellTextView *text_view,
         const gchar *string,
         gint value)
{
	CellEdit *edit = text_view->edit;
	gchar *temp;

	if (value <= 0) return;

	edit->selection_start = MIN (strlen (edit->text), edit->selection_start);

	temp = g_new (gchar, strlen (edit->text) + value + 1);

	strncpy (temp, edit->text, edit->selection_start);
	strncpy (temp + edit->selection_start, string, value);
	strcpy (temp + edit->selection_start + value, edit->text + edit->selection_end);

	g_free (edit->text);

	edit->text = temp;

	edit->selection_start += value;
	edit->selection_end = edit->selection_start;

	g_signal_emit (VIEW_TO_CELL (text_view), signals[TEXT_INSERTED], 0, text_view, edit->selection_end - value, value, edit->row, edit->model_col);
}
