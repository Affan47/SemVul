gwy_app_data_browser_copy_other(GtkTreeModel *model,
                                GtkTreeIter *iter,
                                GtkWidget *window,
                                GwyContainer *container)
{
    GwyDataView *data_view;
    GwyPixmapLayer *layer;
    GwyDataField *dfield;
    GQuark srcquark, targetquark, destquark;
    GObject *object, *destobject;
    const gchar *srckey, *targetkey;
    GwyAppKeyType type;
    gint id;
    gchar *destkey;
    guint len;


    if (!GWY_IS_DATA_WINDOW(window))
        return;


    gtk_tree_model_get(model, iter,
                       MODEL_ID, &srcquark,
                       MODEL_OBJECT, &object,
                       -1);
    if (!object)
        return;
    srckey = g_quark_to_string(srcquark);
    if (!srckey) {
        g_object_unref(object);
        return;
    }
    gwy_debug("DnD: key %08x <%s>, object %p <%s>\n",
               srcquark, srckey, object, G_OBJECT_TYPE_NAME(object));

    id = _gwy_app_analyse_data_key(srckey, &type, &len);

    if (id == -1 || type != KEY_IS_SELECT || !GWY_IS_SELECTION(object)) {
        g_object_unref(object);
        return;
    }


    data_view  = gwy_data_window_get_data_view(GWY_DATA_WINDOW(window));
    layer = gwy_data_view_get_base_layer(data_view);
    targetkey = gwy_pixmap_layer_get_data_key(layer);
    targetquark = g_quark_from_string(targetkey);
    g_return_if_fail(targetquark);
    id = _gwy_app_analyse_data_key(targetkey, &type, NULL);
    g_return_if_fail(id >= 0 && type == KEY_IS_DATA);
    dfield = gwy_container_get_object(container, targetquark);
    g_return_if_fail(GWY_IS_DATA_FIELD(dfield));


    destkey = g_strdup_printf("/%d/select%s", id, srckey+len);
    destquark = g_quark_from_string(destkey);
    g_free(destkey);


    if (!gwy_container_gis_object(container, destquark, &destobject)
        || destobject != object) {
        gdouble xmin, xmax, ymin, ymax;


        xmin = xmax = gwy_data_field_get_xoffset(dfield);
        ymin = ymax = gwy_data_field_get_yoffset(dfield);
        xmax += gwy_data_field_get_xreal(dfield);
        ymax += gwy_data_field_get_yreal(dfield);
        destobject = gwy_serializable_duplicate(G_OBJECT(object));
        gwy_selection_crop(GWY_SELECTION(destobject), xmin, ymin, xmax, ymax);
        if (gwy_selection_get_data(GWY_SELECTION(destobject), NULL))
            gwy_container_set_object(container, destquark, destobject);
        g_object_unref(destobject);
    }

    g_object_unref(object);
}
