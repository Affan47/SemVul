get_custom_text( CUSTOM_TEXT ttype, int index )
{

	static const Glib::ustring activate_text = _( "_Swapon" ) ;
	static const Glib::ustring deactivate_text = _( "_Swapoff" ) ;

	switch ( ttype ) {
		case CTEXT_ACTIVATE_FILESYSTEM :
			return index == 0 ? activate_text : "" ;
		case CTEXT_DEACTIVATE_FILESYSTEM :
			return index == 0 ? deactivate_text : "" ;
		default :
			return "" ;
	}
}
