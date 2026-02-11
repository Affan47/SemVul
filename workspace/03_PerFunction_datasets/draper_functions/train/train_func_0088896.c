on_button_press_event( GdkEventButton * event )
{
	bool ret_val = Gtk::DrawingArea::on_button_press_event( event ) ;

	selected_vp = NULL ;
	set_selected( visual_partitions, static_cast<int>( event ->x ), static_cast<int>( event ->y ) ) ;
	queue_draw() ;

	if ( selected_vp )
	{
		signal_partition_selected .emit( selected_vp ->partition, false ) ;

		if ( event ->type == GDK_2BUTTON_PRESS )
			signal_partition_activated .emit() ;
		else if ( event ->button == 3 )
			signal_popup_menu .emit( event ->button, event ->time ) ;
	}

	return ret_val ;
}
