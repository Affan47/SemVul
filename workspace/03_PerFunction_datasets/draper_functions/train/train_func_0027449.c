update_notify_message(GtkToggleButton *togglebutton,
				  gpointer userdata)
{
  GtkWidget *preferences_dialog=GTK_WIDGET(userdata);
  PanelApplet *applet=PANEL_APPLET(g_object_get_data(G_OBJECT(preferences_dialog), "applet"));

  if(gtk_toggle_button_get_active(togglebutton))
    {
      gint newval=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(togglebutton), "notify_message"));

      gchar *key=g_strdup_printf("%s/notify/notify_message",
				 panel_applet_get_preferences_key(applet));

      GError *err=NULL;

      gconf_client_set_string(confclient,
			      key,
			      gconf_enum_to_string(notify_message_lookup_table,
						   newval),
			      &err);

      handle_gerror("Can't set the notify_message key, is GConf working?\n\nError: %s", &err, false);

      g_free(key);
    }
}
