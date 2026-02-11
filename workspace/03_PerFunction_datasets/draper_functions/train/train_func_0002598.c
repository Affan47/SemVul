Set_Resizer( bool extended )
{
	if ( extended )
		frame_resizer_base = new Frame_Resizer_Extended() ;
	else
	{
		frame_resizer_base = new Frame_Resizer_Base() ;
		frame_resizer_base ->signal_move .connect( sigc::mem_fun( this, &Dialog_Base_Partition::on_signal_move ) );
	}

	frame_resizer_base ->set_border_width( 5 ) ;
	frame_resizer_base ->set_shadow_type( Gtk::SHADOW_ETCHED_OUT );


	frame_resizer_base ->signal_resize .connect( sigc::mem_fun( this, &Dialog_Base_Partition::on_signal_resize ) );

	hbox_resizer .pack_start( *frame_resizer_base, Gtk::PACK_EXPAND_PADDING );

	this ->show_all_children() ;
}
