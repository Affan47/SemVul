messaging_menu_app_set_source_label (MessagingMenuApp *app,
                                     const gchar      *source_id,
                                     const gchar      *label)
{
  Source *source;

  g_return_if_fail (MESSAGING_MENU_IS_APP (app));
  g_return_if_fail (source_id != NULL);
  g_return_if_fail (label != NULL);

  source = messaging_menu_app_get_source (app, source_id);
  if (source)
    {
      g_free (source->label);
      source->label = g_strdup (label);
      messaging_menu_app_notify_source_changed (app, source);
    }
}
