widget_peripherals_general_draw( void *data GCC_UNUSED )
{
  int error;

  if( !widget_peripherals_general_running ) {
    highlight_line = 0;

    settings_copy( &widget_options_settings, &settings_current );
    widget_peripherals_general_running = 1;
  }

  error = widget_options_show_all( options_peripherals_general, &widget_options_settings );
  if( error ) { settings_free( &widget_options_settings ); return error; }

  return 0;
}
