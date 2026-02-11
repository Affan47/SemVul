create_menu_bar( GtkBox *parent, GtkAccelGroup **accel_group )
{
  GError *error = NULL;
  GtkActionGroup *menu_action_group;
  GtkWidget *menu_bar;
  guint ui_menu_id;


  ui_manager_debugger = gtk_ui_manager_new();


  menu_action_group = gtk_action_group_new( "DebuggerActionGroup" );
  gtk_action_group_add_actions( menu_action_group, menu_data, menu_data_count,
                                NULL );
  gtk_action_group_add_toggle_actions( menu_action_group, menu_toggles,
                                       menu_toggles_count, NULL );
  gtk_ui_manager_insert_action_group( ui_manager_debugger, menu_action_group,
                                      0 );
  g_object_unref( menu_action_group );


  ui_menu_id = gtk_ui_manager_add_ui_from_string( ui_manager_debugger,
                                                  debugger_menu,
                                                  sizeof( debugger_menu ),
                                                  &error );
  if( error ) {
    g_error_free( error );
    return 1;
  }
  else if( !ui_menu_id ) return 1;

  *accel_group = gtk_ui_manager_get_accel_group( ui_manager_debugger );

  menu_bar = gtk_ui_manager_get_widget( ui_manager_debugger, "/DebuggerMenu" );

  gtk_box_pack_start( parent, menu_bar, FALSE, FALSE, 0 );

  return 0;
}
