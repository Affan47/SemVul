create_cmd_history_dialog(GtkWindow *parent, World *world)
{
  gchar            *objects[] = { "dlgCmdHistory",
                                  "adjustment1", "adjustment2",
                                  NULL };
  GError           *error = NULL;
  GObject          *dlg;
  GtkTreeView      *viewCommands;
  GtkTreeSelection *selection;
  GtkCellRenderer  *renderer;
  GObject          *btnSendClose;
  GObject          *btnRecallClose;
  GObject          *btnFind;
  GtkSpinButton    *spnDelay;
  GtkSpinButton    *spnNCommands;


  if (!world->ui_builder) {
    world->ui_builder = gtk_builder_new();
  }
  if (!gtk_builder_add_objects_from_file(world->ui_builder,
                                         get_kildclient_installed_file("dlgCmdHistory.ui"),
                                         objects,
                                         &error)) {
    g_warning(_("Error loading UI from XML file: %s"), error->message);
    g_error_free(error);
    return NULL;

  }
  dlg = gtk_builder_get_object(world->ui_builder, "dlgCmdHistory");


  viewCommands = GTK_TREE_VIEW(gtk_builder_get_object(world->ui_builder,
                                                      "viewCommands"));
  gtk_tree_view_set_model(viewCommands, world->cmd_list);
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_data_func(viewCommands,
                                             0,
                                             NULL,
                                             renderer,
                                             (GtkTreeCellDataFunc) completion_cell_data_function,
                                             NULL,
                                             NULL);
  selection = gtk_tree_view_get_selection(viewCommands);
  gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);


  btnSendClose = gtk_builder_get_object(world->ui_builder, "btnSendClose");
  g_object_set_data(btnSendClose, "close", GINT_TO_POINTER(1));
  btnRecallClose = gtk_builder_get_object(world->ui_builder, "btnRecallClose");
  g_object_set_data(btnRecallClose, "close", GINT_TO_POINTER(1));
  btnFind = gtk_builder_get_object(world->ui_builder, "btnFind");
  g_object_set_data(btnFind, "startsearch", GINT_TO_POINTER(1));


  spnDelay = GTK_SPIN_BUTTON(gtk_builder_get_object(world->ui_builder,
                                                    "spnCHDelay"));
  gtk_spin_button_set_value(spnDelay, globalPrefs.multi_cmd_delay);
  spnNCommands = GTK_SPIN_BUTTON(gtk_builder_get_object(world->ui_builder,
                                                        "spnNCommands"));
  gtk_spin_button_set_value(spnNCommands, globalPrefs.multi_cmd_group_size);


  gtk_builder_connect_signals(world->ui_builder, world);

  return GTK_WIDGET(dlg);
}
