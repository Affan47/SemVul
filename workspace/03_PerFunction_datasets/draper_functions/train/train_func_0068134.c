show_configure_cb (GtkWidget            *widget,
                   PeasGtkPluginManager *pm)
{
  PeasGtkPluginManagerView *view = PEAS_GTK_PLUGIN_MANAGER_VIEW (pm->priv->view);
  PeasPluginInfo *info;
  PeasExtension *exten;
  GtkWindow *toplevel;
  GtkWidget *conf_widget = NULL;
  GtkWidget *conf_dlg;
  GtkWidget *vbox;
  GtkWindowGroup *wg;

  info = peas_gtk_plugin_manager_view_get_selected_plugin (view);
  g_return_if_fail (info != NULL);

  exten = peas_engine_create_extension (pm->priv->engine, info, PEAS_GTK_TYPE_CONFIGURABLE, NULL);
  g_return_if_fail (PEAS_IS_EXTENSION (exten));

  conf_widget = peas_gtk_configurable_create_configure_widget (PEAS_GTK_CONFIGURABLE (exten));
  g_object_unref (exten);

  g_return_if_fail (GTK_IS_WIDGET (conf_widget));
  g_return_if_fail (!gtk_widget_is_toplevel (conf_widget));

  toplevel = GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (pm)));

  conf_dlg = gtk_dialog_new_with_buttons (peas_plugin_info_get_name (info),
                                          toplevel,
                                          0,
                                          GTK_STOCK_CLOSE,
                                          GTK_RESPONSE_CLOSE,
                                          NULL);

  vbox = gtk_dialog_get_content_area (GTK_DIALOG (conf_dlg));
  gtk_box_pack_start (GTK_BOX (vbox), conf_widget, TRUE, TRUE, 0);

  if (peas_plugin_info_get_help_uri (info) != NULL)
    {
      GtkWidget *hbuttonbox;
      GtkWidget *help_button;

      hbuttonbox = gtk_dialog_get_action_area (GTK_DIALOG (conf_dlg));
      help_button = gtk_button_new_from_stock (GTK_STOCK_HELP);
      gtk_container_add (GTK_CONTAINER (hbuttonbox), help_button);
      gtk_button_box_set_child_secondary (GTK_BUTTON_BOX (hbuttonbox),
                                          help_button, TRUE);

      g_signal_connect (help_button,
                        "clicked",
                        G_CALLBACK (help_button_cb),
                        info);
    }

  if (gtk_window_has_group (toplevel))
    {
      wg = gtk_window_get_group (toplevel);
    }
  else
    {
      wg = gtk_window_group_new ();
      gtk_window_group_add_window (wg, toplevel);
    }

  gtk_window_group_add_window (wg, GTK_WINDOW (conf_dlg));

  gtk_window_set_transient_for (GTK_WINDOW (conf_dlg), toplevel);
  gtk_window_set_modal (GTK_WINDOW (conf_dlg), TRUE);
  gtk_widget_show_all (conf_dlg);

  g_signal_connect (conf_dlg,
                    "response",
                    G_CALLBACK (gtk_widget_destroy),
                    NULL);
}
