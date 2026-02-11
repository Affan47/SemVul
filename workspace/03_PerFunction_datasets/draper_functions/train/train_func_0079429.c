gwa_action_lookup (GList *actions, const gchar *action_id)
{
  GList *l;

  for (l = actions; l; l = g_list_next (l))
    {
      GWActionClass *action = l->data;
      if (strcmp (action->id, action_id) == 0)
        return action;
    }

  return NULL;
}
