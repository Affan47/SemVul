disconnect_profiles_from_actions_in_group (GtkActionGroup *action_group)
{
  GList *actions, *l;

  actions = gtk_action_group_list_actions (action_group);
  for (l = actions; l != NULL; l = l->next)
    {
      GObject *action = G_OBJECT (l->data);
      TerminalProfile *profile;

      profile = g_object_get_data (action, PROFILE_DATA_KEY);
      if (!profile)
        continue;

      g_signal_handlers_disconnect_by_func (profile, G_CALLBACK (profile_visible_name_notify_cb), action);
    }
  g_list_free (actions);
}
