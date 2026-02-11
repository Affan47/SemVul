screenshot_application_startup (GApplication *app)
{
  ScreenshotApplication *self = SCREENSHOT_APPLICATION (app);
  GtkBuilder *builder;
  GMenuModel *menu;

  G_APPLICATION_CLASS (screenshot_application_parent_class)->startup (app);

  gtk_window_set_default_icon_name (SCREENSHOOTER_ICON);
  screenshooter_init_stock_icons ();

  g_action_map_add_action_entries (G_ACTION_MAP (self), action_entries,
                                   G_N_ELEMENTS (action_entries), self);

  builder = gtk_builder_new ();
  gtk_builder_add_from_resource (builder, "/org/gnome/screenshot/screenshot-app-menu.ui", NULL);
  menu = G_MENU_MODEL (gtk_builder_get_object (builder, "app-menu"));
  gtk_application_set_app_menu (GTK_APPLICATION (self), menu);

  g_object_unref (builder);
  g_object_unref (menu);


  if (screenshot_config->interactive)
    screenshot_show_interactive_dialog (self);
  else
    screenshot_start (self);
}
