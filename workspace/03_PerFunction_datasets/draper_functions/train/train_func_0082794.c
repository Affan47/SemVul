install_options_menu (AisleriotWindow *window)
{
  AisleriotWindowPrivate *priv = window->priv;
  GList *options, *l;
  int options_value = 0;
  GSList *radiogroup = NULL;
  int radion = 0;

  if (priv->options_merge_id != 0) {
    gtk_ui_manager_remove_ui (priv->ui_manager, priv->options_merge_id);
    priv->options_merge_id = 0;
  }

  if (priv->options_group) {
    gtk_ui_manager_remove_action_group (priv->ui_manager, priv->options_group);
    priv->options_group = NULL;
  }


  gtk_ui_manager_ensure_update (priv->ui_manager);


  if (aisleriot_conf_get_options (aisleriot_game_get_game_module (priv->game), &options_value)) {
    aisleriot_game_change_options (priv->game, AISLERIOT_GAME_OPTIONS_MAX, options_value);
  }


  options = aisleriot_game_get_options (priv->game);
  if (!options)
    return;

  priv->options_group = gtk_action_group_new ("Options");
  gtk_ui_manager_insert_action_group (priv->ui_manager, priv->options_group, -1);
  g_object_unref (priv->options_group);

  priv->options_merge_id = gtk_ui_manager_new_merge_id (priv->ui_manager);

  for (l = options; l != NULL; l = l->next) {
    AisleriotGameOption *option = (AisleriotGameOption *) l->data;
    GtkToggleAction *action;
    gchar actionname[32];

    g_snprintf (actionname, sizeof (actionname), "Option%u", option->value);

    if (option->type == AISLERIOT_GAME_OPTION_CHECK) {
      action = gtk_toggle_action_new (actionname,
                                      option->display_name,
                                      NULL,
                                      NULL );
      radiogroup = NULL;
      radion = 0;
    } else {
      action = GTK_TOGGLE_ACTION (gtk_radio_action_new (actionname,
                                                        option->display_name,
                                                        NULL,
                                                        NULL ,
                                                        radion++));
      gtk_radio_action_set_group (GTK_RADIO_ACTION (action),
                                  radiogroup);
      radiogroup = gtk_radio_action_get_group (GTK_RADIO_ACTION (action));
    }

    gtk_toggle_action_set_active (action, option->set);
    g_signal_connect (action, "toggled",
                      G_CALLBACK (option_cb), window);

    gtk_action_group_add_action (priv->options_group, GTK_ACTION (action));
    g_object_unref (action);

    gtk_ui_manager_add_ui (priv->ui_manager,
                           priv->options_merge_id,
                           OPTIONS_MENU_PATH,
                           actionname, actionname,
                           GTK_UI_MANAGER_MENUITEM, FALSE);

    aisleriot_game_option_free (option);
  }

  g_list_free (options);
}
