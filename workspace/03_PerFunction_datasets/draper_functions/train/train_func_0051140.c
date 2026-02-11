exo_icon_view_accessible_model_row_deleted (GtkTreeModel *tree_model,
                                            GtkTreePath  *path,
                                            gpointer     user_data)
{
  ExoIconViewAccessiblePrivate *priv;
  ExoIconViewItemAccessibleInfo *info;
  ExoIconViewAccessible *view;
  ExoIconViewItemAccessible *item;
  GList *items;
  GList *tmp_list;
  GList *deleted_item;
  AtkObject *atk_obj;
  gint index;

  index = gtk_tree_path_get_indices(path)[0];
  atk_obj = gtk_widget_get_accessible (GTK_WIDGET (user_data));
  view = EXO_ICON_VIEW_ACCESSIBLE (atk_obj);
  priv = exo_icon_view_accessible_get_priv (atk_obj);

  items = priv->items;
  tmp_list = NULL;
  deleted_item = NULL;
  info = NULL;
  while (items)
    {
      info = items->data;
      item = EXO_ICON_VIEW_ITEM_ACCESSIBLE (info->item);
      if (info->index == index)
        {
          deleted_item = items;
        }
      if (info->index != item->item->index)
        {
          if (tmp_list == NULL)
            tmp_list = items;

          info->index = item->item->index;
        }

      items = items->next;
    }
  exo_icon_view_accessible_traverse_items (view, tmp_list);
  if (deleted_item)
    {
      info = deleted_item->data;
      exo_icon_view_item_accessible_add_state (EXO_ICON_VIEW_ITEM_ACCESSIBLE (info->item), ATK_STATE_DEFUNCT, TRUE);
      g_signal_emit_by_name (atk_obj, "children-changed::remove",
                             index, NULL, NULL);
      priv->items = g_list_remove_link (priv->items, deleted_item);
      g_free (info);
    }

  return;
}
