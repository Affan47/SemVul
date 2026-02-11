garcon_menu_merger_get_file (GarconMenuTreeProvider *provider)
{
  GarconMenuTreeProvider *provider_;

  g_return_val_if_fail (GARCON_IS_MENU_MERGER (provider), NULL);

  provider_ = GARCON_MENU_MERGER (provider)->priv->tree_provider;
  return garcon_menu_tree_provider_get_file (provider_);
}
