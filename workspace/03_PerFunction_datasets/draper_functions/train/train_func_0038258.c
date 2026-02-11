if2_eject( void )
{
  if ( !periph_is_active( PERIPH_TYPE_INTERFACE2 ) ) {
    ui_error( UI_ERROR_ERROR,
	      "This machine does not support the Interface 2" );
    return;
  }

  if( settings_current.if2_file ) free( settings_current.if2_file );
  settings_current.if2_file = NULL;

  machine_current->ram.romcs = 0;

  ui_menu_activate( UI_MENU_ITEM_MEDIA_CARTRIDGE_IF2_EJECT, 0 );

  machine_reset( 0 );
}
