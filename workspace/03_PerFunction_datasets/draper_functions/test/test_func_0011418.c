ui_debugger_activate( void )
{
  int error;

  fuse_emulation_pause();


  if( !dialog_created ) if( create_dialog() ) return 1;

  gtk_widget_show_all( dialog );
  error = hide_hidden_panes(); if( error ) return error;

  gtk_widget_set_sensitive( continue_button, 1 );
  gtk_widget_set_sensitive( break_button, 0 );
  if( !debugger_active ) activate_debugger();

  return 0;
}
