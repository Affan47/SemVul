stop_cell_editing (NemoListView *list_view)
{
	GtkTreeViewColumn *column;


	column = list_view->details->file_name_column;
	if (column != NULL && list_view->details->editable_widget != NULL &&
	    GTK_IS_CELL_EDITABLE (list_view->details->editable_widget)) {
		gtk_cell_editable_editing_done (list_view->details->editable_widget);
	}
}
