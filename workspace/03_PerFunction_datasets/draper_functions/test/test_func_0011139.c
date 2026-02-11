_remove_selected_pictures (FrogrMainView *self)
{
  FrogrMainViewPrivate *priv = FROGR_MAIN_VIEW_GET_PRIVATE (self);
  GSList *selected_pictures;
  GSList *item;

  if (!_pictures_selected_required_check (self))
    return;


  selected_pictures = _get_selected_pictures (self);
  for (item = selected_pictures; item; item = g_slist_next (item))
    {
      FrogrPicture *picture = FROGR_PICTURE (item->data);
      frogr_model_remove_picture (priv->model, picture);
    }


  _update_ui (self);


  g_slist_foreach (selected_pictures, (GFunc)g_object_unref, NULL);
  g_slist_free (selected_pictures);
}
