on_selection_changed()
{
	if ( ! block && treeselection ->get_selected() != 0 )
	{
		Gtk::TreeRow row = static_cast<Gtk::TreeRow>( * treeselection ->get_selected() ) ;
		signal_partition_selected .emit( row[ treeview_detail_columns .partition ], true ) ;
	}
}
