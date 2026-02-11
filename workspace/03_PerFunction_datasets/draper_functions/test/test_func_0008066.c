garcon_menu_get_layout (GarconMenu *menu,
                        gboolean    default_only)
{
  GNode *layout = NULL;

  g_return_val_if_fail (GARCON_IS_MENU (menu), NULL);

  if (G_LIKELY (!default_only))
    {
      layout = garcon_menu_node_tree_get_child_node (menu->priv->tree,
                                                     GARCON_MENU_NODE_TYPE_LAYOUT,
                                                     TRUE);
    }

  if (layout == NULL)
    {
      layout = garcon_menu_node_tree_get_child_node (menu->priv->tree,
                                                     GARCON_MENU_NODE_TYPE_DEFAULT_LAYOUT,
                                                     TRUE);

      if (layout == NULL && menu->priv->parent != NULL)
        layout = garcon_menu_get_layout (menu->priv->parent, TRUE);
    }

  return layout;
}
