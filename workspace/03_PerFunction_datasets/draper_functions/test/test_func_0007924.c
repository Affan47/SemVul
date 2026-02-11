photos_selection_toolbar_favorite_clicked (GtkButton *button, gpointer user_data)
{
  PhotosSelectionToolbar *self = PHOTOS_SELECTION_TOOLBAR (user_data);
  PhotosSelectionToolbarPrivate *priv = self->priv;
  GList *selection;
  GList *l;

  if (priv->inside_refresh)
    return;

  selection = photos_selection_controller_get_selection (priv->sel_cntrlr);
  for (l = selection; l != NULL; l = l->next)
    {
      const gchar *urn = (gchar *) l->data;
      PhotosBaseItem *item;
      gboolean favorite;

      item = PHOTOS_BASE_ITEM (photos_base_manager_get_object_by_id (priv->item_mngr, urn));
      favorite = photos_base_item_is_favorite (item);
      photos_base_item_set_favorite (item, !favorite);
    }

  photos_selection_controller_set_selection_mode (priv->sel_cntrlr, FALSE);
}
