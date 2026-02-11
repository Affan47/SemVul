get_notify_message(PanelApplet *applet)
{
  gint curval=NOTIFY_MESSAGE_SECURITY;

  gchar *key=g_strdup_printf("%s/notify/notify_message",
			     panel_applet_get_preferences_key(applet));

  GError *err=NULL;

  gchar *stringval=gconf_client_get_string(confclient,
					   key,
					   &err);

  if(err)
    g_error_free(err);

  if(stringval)
    gconf_string_to_enum(notify_message_lookup_table,
			 stringval,
			 &curval);

  g_free(stringval);
  g_free(key);

  return (NotifyMessage) curval;
}
