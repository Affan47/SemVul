gwy_app_data_proxy_brick_set_visible(GwyAppDataProxy *proxy,
                                     GtkTreeIter *iter,
                                     gboolean visible)
{
    GwyAppDataList *list;
    GtkTreeModel *model;
    GtkWidget *widget, *window;
    GObject *object;
    gint id;

    list = &proxy->lists[PAGE_VOLUMES];
    model = GTK_TREE_MODEL(list->store);

    gtk_tree_model_get(model, iter,
                       MODEL_WIDGET, &widget,
                       MODEL_OBJECT, &object,
                       MODEL_ID, &id,
                       -1);
    if (visible == (widget != NULL)) {
        g_object_unref(object);
        gwy_object_unref(widget);
        return FALSE;
    }

    if (visible) {
        widget = gwy_app_data_browser_create_volume(proxy->parent, proxy, id);
        gtk_list_store_set(list->store, iter, MODEL_WIDGET, widget, -1);
        list->visible_count++;
    }
    else {
        gwy_app_data_proxy_update_visibility(object, FALSE);
        window = gtk_widget_get_ancestor(widget, GWY_TYPE_DATA_WINDOW);
        gtk_widget_destroy(window);
        gtk_list_store_set(list->store, iter, MODEL_WIDGET, NULL, -1);
        g_object_unref(widget);
        list->visible_count--;
        update_brick_sens();
    }
    g_object_unref(object);

    gwy_debug("visible_count: %d", list->visible_count);

    return TRUE;
}
