drag_data_received(GtkTreeDragDest   *drag_dest,
				   GtkTreePath       *dest,
				   GtkSelectionData  *selection_data)
{
	LOG(LOG_DEBUG, "IN : drag_data_received()");
	edited = FALSE;
	LOG(LOG_DEBUG, "OUT : drag_data_received()");
	return(FALSE);

}
