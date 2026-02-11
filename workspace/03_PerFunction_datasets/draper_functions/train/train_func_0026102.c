_e2_output_activated_cb (E2_OutputTabRuntime *rt)
{
	printd (DEBUG, "output activated cb");
	GtkTextIter start, end;
	if (gtk_text_buffer_get_selection_bounds (rt->buffer, &start, &end))
	{
		gchar *seltext = gtk_text_buffer_get_text (rt->buffer, &start, &end, FALSE);
		printd (DEBUG, "output text is %s", seltext);
		_e2_output_open_text (seltext, TRUE);
		g_free (seltext);


		return TRUE;
	}
	printd (DEBUG, "nothing selected in output");

	return FALSE;
}
