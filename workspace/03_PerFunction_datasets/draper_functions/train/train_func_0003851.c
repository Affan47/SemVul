exo_icon_view_item_accessible_action_set_description (AtkAction   *action,
                                                      gint         i,
                                                      const gchar *description)
{
  ExoIconViewItemAccessible *item;

  if (i < 0 || i >= LAST_ACTION)
    return FALSE;

  item = EXO_ICON_VIEW_ITEM_ACCESSIBLE (action);

  g_free (item->action_descriptions[i]);

  item->action_descriptions[i] = g_strdup (description);

  return TRUE;
}
