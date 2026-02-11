custom_item_activated_cb (GtkAppChooserButton *button,
                          const gchar *item,
                          gpointer user_data)
{
  CcInfoPanel *self = user_data;
  gchar *content_type;

  content_type = gtk_app_chooser_get_content_type (GTK_APP_CHOOSER (button));

  if (g_strcmp0 (item, CUSTOM_ITEM_ASK) == 0) {
    autorun_set_preferences (self, content_type,
                             FALSE, FALSE, FALSE);
  } else if (g_strcmp0 (item, CUSTOM_ITEM_OPEN_FOLDER) == 0) {
    autorun_set_preferences (self, content_type,
                             FALSE, FALSE, TRUE);
  } else if (g_strcmp0 (item, CUSTOM_ITEM_DO_NOTHING) == 0) {
    autorun_set_preferences (self, content_type,
                             FALSE, TRUE, FALSE);
  }

  g_free (content_type);
}
