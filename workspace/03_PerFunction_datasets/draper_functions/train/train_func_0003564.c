close_dialog (GtkWidget *button,
              gpointer data)
{
	PagerData *pager = data;
	GtkTreeViewColumn *col;
	GtkCellArea *area;
	GtkCellEditable *edit_widget;


	col = gtk_tree_view_get_column (GTK_TREE_VIEW (pager->workspaces_tree), 0);
	area = gtk_cell_layout_get_area (GTK_CELL_LAYOUT (col));
	edit_widget = gtk_cell_area_get_edit_widget (area);

	if (edit_widget)
		gtk_cell_editable_editing_done (edit_widget);

	gtk_widget_destroy (pager->properties_dialog);
}
