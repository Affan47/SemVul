categ_drag_data_get ( GtkTreeDragSource * drag_source, GtkTreePath * path,
			       GtkSelectionData * selection_data )
{
    if ( path )
    {
	gtk_tree_set_row_drag_data (selection_data,
				    GTK_TREE_MODEL(categ_tree_model), path);
    }

    return FALSE;
}
