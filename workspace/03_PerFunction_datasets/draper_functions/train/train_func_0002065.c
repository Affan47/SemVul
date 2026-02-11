main_window_create(void){

  create_app_main_window(_("gPHPEdit"));
  main_window_create_prinbox();


  main_window.menu = menubar_new ();
  gtk_box_pack_start (GTK_BOX (main_window.prinbox), main_window.menu, FALSE, FALSE, 0);
  gtk_widget_show_all (main_window.menu);

  main_window.toolbar_main = toolbar_new ();
  gtk_box_pack_start (GTK_BOX (main_window.prinbox), main_window.toolbar_main, FALSE, FALSE, 0);
  if (get_preferences_manager_show_maintoolbar(main_window.prefmg)) gtk_widget_show (main_window.toolbar_main);

  main_window.symbolmg = symbol_manager_new();

  main_window_create_panes();
  main_window_fill_panes();
  main_window_create_appbar();

  g_signal_connect (G_OBJECT (main_window.window), "delete_event", G_CALLBACK(main_window_delete_event), NULL);
  g_signal_connect (G_OBJECT (main_window.window), "destroy", G_CALLBACK (main_window_destroy_event), NULL);
  g_signal_connect (G_OBJECT (main_window.window), "key_press_event", G_CALLBACK (main_window_key_press_event), NULL);
  g_signal_connect (G_OBJECT (main_window.window), "size_allocate", G_CALLBACK (main_window_resize), NULL);
  g_signal_connect (G_OBJECT (main_window.window), "window-state-event", G_CALLBACK (main_window_state_changed), NULL);
  g_signal_connect (G_OBJECT (main_window.window), "focus-in-event", G_CALLBACK (main_window_activate_focus), NULL);

  gtk_widget_show(main_window.window);

  update_app_title(document_manager_get_current_documentable(main_window.docmg));

  main_window.stylemg = gtk_source_style_scheme_manager_new ();
  gchar *theme_dir = g_build_path (G_DIR_SEPARATOR_S, API_DIR, "themes", NULL);
  gtk_source_style_scheme_manager_prepend_search_path (main_window.stylemg, theme_dir);
  g_free(theme_dir);
}
