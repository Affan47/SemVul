fm_app_menu_view_is_item_app(GtkTreeView* view, GtkTreeIter* it)
{
    MenuCacheItem* item;

    gboolean ret = FALSE;
    gtk_tree_model_get(GTK_TREE_MODEL(store), it, COL_ITEM, &item, -1);
    if(item && menu_cache_item_get_type(item) == MENU_CACHE_TYPE_APP)
        ret = TRUE;
    return ret;
}
