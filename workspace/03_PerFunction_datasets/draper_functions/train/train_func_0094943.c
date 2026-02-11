glade_widget_set_pack_action_sensitive (GladeWidget * widget,
                                        const gchar * action_path,
                                        gboolean sensitive)
{
  GladeWidgetAction *action;

  g_return_val_if_fail (GLADE_IS_WIDGET (widget), FALSE);

  if ((action = glade_widget_get_pack_action (widget, action_path)) != NULL)
    {
      glade_widget_action_set_sensitive (action, sensitive);
      return TRUE;
    }
  return FALSE;
}
