apply_option (GtkToggleAction *action,
              guint32 *changed_mask,
              guint32 *changed_value)
{
  gboolean active;
  const char *action_name;
  guint32 value;

  active = gtk_toggle_action_get_active (action);

  action_name = gtk_action_get_name (GTK_ACTION (action));
  value = g_ascii_strtoull (action_name + strlen ("Option"), NULL, 10);


  *changed_mask |= value;
  if (active)
    *changed_value |= value;
}
