we_lplugin_help_cb(gpointer data, GtkButton *button)
{
  World            *world;
  GtkTreeView      *view;
  GtkTreeModel     *model;
  GtkTreeSelection *selection;
  GtkTreeIter       iter;

  view = (GtkTreeView *) data;
  world = (World *) g_object_get_data(G_OBJECT(view), "forworld");
  selection = gtk_tree_view_get_selection(view);
  if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
    Plugin    *plugin;
    gchar     *cmd;
    GtkWidget *msgdlg;

    gtk_tree_model_get(model, &iter, WE_GUIED_POINTER, &plugin, -1);
    cmd = g_strdup_printf("%s::help();", plugin->name);
    PERL_SET_CONTEXT(world->perl_interpreter);
    eval_pv(cmd, FALSE);
    g_free(cmd);


    if (!globalPrefs.no_plugin_help_msg) {
      GtkWidget *chk;
      msgdlg = gtk_message_dialog_new(GTK_WINDOW(world->dlgEditWorld),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_INFO,
                                      GTK_BUTTONS_OK,
                                      _("The help is displayed in main window."));
      gtk_window_set_title(GTK_WINDOW(msgdlg), _("KildClient Information"));
      chk = gtk_check_button_new_with_mnemonic(_("_Do not display this message again"));
      gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(msgdlg))),
                         chk,
                         FALSE, FALSE, 4);

      gtk_widget_show_all(msgdlg);
      gtk_dialog_run(GTK_DIALOG(msgdlg));

      if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chk))) {
        globalPrefs.no_plugin_help_msg = TRUE;
      }

      gtk_widget_destroy(msgdlg);
    }
  }
}
