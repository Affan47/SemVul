gwy_plain_tool_set_selection_key(GwyPlainTool *plain_tool,
                                 const gchar *bname)
{
    GwyPixmapLayer *layer;
    const gchar *data_key;
    gchar *key;
    guint len;

    gwy_debug("%s", bname);
    g_return_val_if_fail(GWY_IS_PLAIN_TOOL(plain_tool), NULL);
    g_return_val_if_fail(GWY_IS_DATA_VIEW(plain_tool->data_view), NULL);
    g_return_val_if_fail(GWY_IS_VECTOR_LAYER(plain_tool->layer), NULL);
    g_return_val_if_fail(bname, NULL);

    layer = gwy_data_view_get_base_layer(plain_tool->data_view);
    data_key = gwy_pixmap_layer_get_data_key(layer);
    gwy_debug("data_key: <%s>", data_key);
    len = strlen(data_key);
    g_return_val_if_fail(len > 5 && gwy_strequal(data_key + len-5, "/data"),
                         NULL);

    key = g_strdup_printf("%.*s/select/%s", len-5, data_key, bname);
    gwy_vector_layer_set_selection_key(plain_tool->layer, key);
    gwy_debug("selection key: <%s>", key);
    g_free(key);

    gwy_vector_layer_ensure_selection(plain_tool->layer);


    return gwy_vector_layer_get_selection_key(plain_tool->layer);
}
