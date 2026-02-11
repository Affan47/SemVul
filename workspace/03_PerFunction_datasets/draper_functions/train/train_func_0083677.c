gwy_app_data_proxy_add_object(GwyAppDataList *list,
                              gint i,
                              GtkTreeIter *iter,
                              GObject *object)
{
    gtk_list_store_insert_with_values(list->store, iter, G_MAXINT,
                                      MODEL_ID, i,
                                      MODEL_OBJECT, object,
                                      MODEL_WIDGET, NULL,
                                      MODEL_THUMBNAIL, NULL,
                                      -1);
    if (list->last < i)
        list->last = i;
}
