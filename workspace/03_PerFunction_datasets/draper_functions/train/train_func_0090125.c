bar_sort_undo_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;

	if (sd->mode == BAR_SORT_MODE_FOLDER)
		{
		bar_sort_undo_folder(sd, button);
		}
	else
		{
		bar_sort_undo_collection(sd);
		}
}
