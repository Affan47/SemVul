selClear()
{
	int start;

	if (!entry)
		return;

	gtk_editable_get_selection_bounds(GTK_EDITABLE(entry),&start,NULL);
	gtk_editable_select_region(GTK_EDITABLE(entry),start,start);
}
