remove_path_item(GtkListStore* model, FmPlacesOrder id)
{
    FmPlacesItem* item;
    GtkTreeIter it;

    if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &it)) do
    {
        item = NULL;
        gtk_tree_model_get(GTK_TREE_MODEL(model), &it, FM_PLACES_MODEL_COL_INFO, &item, -1);
        if(!item || item->type != FM_PLACES_ITEM_PATH || item->id > id)
            return;
        if(item->id == id)
        {
            gtk_list_store_remove(model, &it);
            place_item_free(item);
            return;
        }
    } while(gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &it));
}
