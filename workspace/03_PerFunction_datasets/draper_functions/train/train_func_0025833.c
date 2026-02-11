gwy_app_data_browser_render_channel(G_GNUC_UNUSED GtkTreeViewColumn *column,
                                    GtkCellRenderer *renderer,
                                    GtkTreeModel *model,
                                    GtkTreeIter *iter,
                                    G_GNUC_UNUSED gpointer userdata)
{
    GwyContainer *container;
    GObject *object;
    GdkPixbuf *pixbuf;
    gdouble timestamp, *pbuf_timestamp = NULL;
    GtkWidget *data_view;
    gint id;

    gtk_tree_model_get(model, iter,
                       MODEL_ID, &id,
                       MODEL_OBJECT, &object,
                       MODEL_TIMESTAMP, &timestamp,
                       MODEL_THUMBNAIL, &pixbuf,
                       MODEL_WIDGET, &data_view,
                       -1);

    container = g_object_get_qdata(object, container_quark);
    g_object_unref(object);

    if (pixbuf) {
        pbuf_timestamp = (gdouble*)g_object_get_data(G_OBJECT(pixbuf),
                                                     "timestamp");
        if (*pbuf_timestamp >= timestamp) {
            g_object_set(renderer, "pixbuf", pixbuf, NULL);
            g_object_unref(pixbuf);
            gwy_object_unref(data_view);
            return;
        }
    }

    pixbuf = gwy_app_get_channel_thumbnail(container, id,
                                           THUMB_SIZE, THUMB_SIZE);
    pbuf_timestamp = g_new(gdouble, 1);
    *pbuf_timestamp = gwy_get_timestamp();
    g_object_set_data_full(G_OBJECT(pixbuf), "timestamp", pbuf_timestamp,
                           g_free);
    gtk_list_store_set(GTK_LIST_STORE(model), iter,
                       MODEL_THUMBNAIL, pixbuf,
                       -1);
    g_object_set(renderer, "pixbuf", pixbuf, NULL);

    if (data_view) {
        GtkWidget *window = gtk_widget_get_toplevel(data_view);

        if (window && GTK_IS_WINDOW(window))
            gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
        g_object_unref(data_view);
    }

    g_object_unref(pixbuf);
}
