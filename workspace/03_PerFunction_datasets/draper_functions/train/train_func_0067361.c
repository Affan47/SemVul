garcon_menu_get_elements (GarconMenu *menu)
{
  GarconMenuLayoutMergeType merge_type;
  GarconMenuNodeType        type;
  GarconMenuItem           *item;
  GarconMenu               *submenu;
  GList                    *items = NULL;
  GList                    *menu_items;
  GNode                    *layout = NULL;
  GNode                    *node;

  g_return_val_if_fail (GARCON_IS_MENU (menu), NULL);


  layout = garcon_menu_get_layout (menu, FALSE);


  g_return_val_if_fail (layout != NULL, NULL);


  for (node = g_node_first_child (layout); node != NULL; node = g_node_next_sibling (node))
    {

      type = garcon_menu_node_tree_get_node_type (node);

      if (type == GARCON_MENU_NODE_TYPE_FILENAME)
        {

          item = garcon_menu_item_pool_lookup (menu->priv->pool,
                                               garcon_menu_node_tree_get_string (node));


          if (G_LIKELY (item != NULL))
            items = g_list_prepend (items, item);
        }
      else if (type == GARCON_MENU_NODE_TYPE_MENUNAME)
        {

          submenu = garcon_menu_get_menu_with_name (menu,
                                                    garcon_menu_node_tree_get_string (node));


          if (G_LIKELY (submenu != NULL))
            items = g_list_prepend (items, submenu);
        }
      else if (type == GARCON_MENU_NODE_TYPE_SEPARATOR)
        {

          items = g_list_prepend (items, garcon_menu_separator_get_default ());
        }
      else if (type == GARCON_MENU_NODE_TYPE_MERGE)
        {

          merge_type = garcon_menu_node_tree_get_layout_merge_type (node);

          if (merge_type == GARCON_MENU_LAYOUT_MERGE_ALL)
            {

              menu_items = g_list_copy (menu->priv->submenus);


              garcon_menu_item_pool_foreach (menu->priv->pool, (GHFunc) items_collect, &menu_items);


              menu_items = g_list_sort (menu_items, (GCompareFunc) garcon_menu_compare_items);


              layout_elements_collect (&items, menu_items, layout);


              g_list_free (menu_items);
            }
          else if (merge_type == GARCON_MENU_LAYOUT_MERGE_FILES)
            {

              menu_items = garcon_menu_get_items (menu);


              layout_elements_collect (&items, menu_items, layout);


              g_list_free (menu_items);
            }
          else if (merge_type == GARCON_MENU_LAYOUT_MERGE_MENUS)
            {

              menu_items = garcon_menu_get_menus (menu);


              layout_elements_collect (&items, menu_items, layout);


              g_list_free (menu_items);
            }
        }
    }

  return g_list_reverse (items);
}
