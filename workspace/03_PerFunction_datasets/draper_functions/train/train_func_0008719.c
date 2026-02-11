exo_icon_view_set_search_position_func (ExoIconView                  *icon_view,
                                        ExoIconViewSearchPositionFunc search_position_func,
                                        gpointer                      search_position_data,
                                        GDestroyNotify                search_position_destroy)
{
  g_return_if_fail (EXO_IS_ICON_VIEW (icon_view));
  g_return_if_fail (search_position_func != NULL || (search_position_data == NULL && search_position_destroy == NULL));


  if (icon_view->priv->search_position_destroy != NULL)
    (*icon_view->priv->search_position_destroy) (icon_view->priv->search_position_data);

  icon_view->priv->search_position_func = (search_position_func != NULL) ? search_position_func : exo_icon_view_search_position_func;
  icon_view->priv->search_position_data = search_position_data;
  icon_view->priv->search_position_destroy = search_position_destroy;
}
