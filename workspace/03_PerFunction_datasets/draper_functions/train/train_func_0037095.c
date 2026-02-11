create_test_triggers_dialog(GtkWindow *parent, World *world)
{
  GError           *error = NULL;
  GObject          *dlg;


  if (!world->ui_builder) {
    world->ui_builder = gtk_builder_new();
  }
  if (!gtk_builder_add_from_file(world->ui_builder,
                                 get_kildclient_installed_file("dlgTestTriggers.ui"),
                                 &error)) {
    g_warning(_("Error loading UI from XML file: %s"), error->message);
    g_error_free(error);
    return NULL;

  }
  dlg      = gtk_builder_get_object(world->ui_builder, "dlgTestTriggers");


  gtk_builder_connect_signals(world->ui_builder, world);

  return GTK_WIDGET(dlg);
}
