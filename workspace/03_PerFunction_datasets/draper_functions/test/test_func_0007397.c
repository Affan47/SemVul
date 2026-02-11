gwy_app_data_browser_reset_visibility(GwyContainer *data,
                                      GwyVisibilityResetType reset_type)
{
    static const SetVisibleFunc set_visible[NPAGES] = {
        &gwy_app_data_proxy_channel_set_visible,
        &gwy_app_data_proxy_graph_set_visible,
        NULL,
        &gwy_app_data_proxy_brick_set_visible,
    };

    GwyAppDataBrowser *browser;
    GwyAppDataProxy *proxy = NULL;
    GwyAppDataList *list;
    gboolean visible;
    gint i;

    g_return_val_if_fail(GWY_IS_CONTAINER(data), FALSE);

    if (gui_disabled)
        return FALSE;

    if ((browser = gwy_app_data_browser))
        proxy = gwy_app_data_browser_get_proxy(browser, data, FALSE);

    if (!proxy) {
        g_critical("Data container is unknown to data browser.");
        return FALSE;
    }

    if (reset_type == GWY_VISIBILITY_RESET_RESTORE
        || reset_type == GWY_VISIBILITY_RESET_DEFAULT) {
        for (i = 0; i < NPAGES; i++) {
            if (set_visible[i])
                gwy_app_data_list_reconstruct_visibility(proxy,
                                                         &proxy->lists[i],
                                                         set_visible[i]);
        }
        if (gwy_app_data_proxy_visible_count(proxy))
            return TRUE;


        if (reset_type == GWY_VISIBILITY_RESET_RESTORE)
            return FALSE;


        for (i = 0; i < NPAGES; i++) {
            GtkTreeModel *model;
            GtkTreeIter iter;

            if (!set_visible[i])
                continue;

            list = &proxy->lists[i];
            model = GTK_TREE_MODEL(list->store);
            if (!gtk_tree_model_get_iter_first(model, &iter))
                continue;

            proxy->resetting_visibility = TRUE;
            set_visible[i](proxy, &iter, TRUE);
            proxy->resetting_visibility = FALSE;
        }

        return FALSE;
    }

    if (reset_type == GWY_VISIBILITY_RESET_HIDE_ALL)
        visible = FALSE;
    else if (reset_type == GWY_VISIBILITY_RESET_SHOW_ALL)
        visible = TRUE;
    else {
        g_critical("Wrong reset_type value");
        return FALSE;
    }

    proxy->resetting_visibility = TRUE;
    for (i = 0; i < NPAGES; i++) {
        if (set_visible[i])
            gwy_app_data_list_reset_visibility(proxy, &proxy->lists[i],
                                               set_visible[i], visible);
    }
    proxy->resetting_visibility = FALSE;

    return visible && gwy_app_data_proxy_visible_count(proxy);
}
