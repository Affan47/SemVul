model_has_action (ExoToolbarsModel *model,
                  GtkAction        *action)
{
  const gchar *action_name;
  const gchar *id;
  gboolean     is_separator;
  gint         i;
  gint         j;

  action_name = gtk_action_get_name (action);

  for (i = 0; i < exo_toolbars_model_n_toolbars (model); ++i)
    for (j = 0; j < exo_toolbars_model_n_items (model, i); ++j)
      {
        exo_toolbars_model_item_nth (model, i, j, &is_separator, &id, NULL);
        if (!is_separator && exo_str_is_equal (id, action_name))
          return TRUE;
      }

  return FALSE;
}
