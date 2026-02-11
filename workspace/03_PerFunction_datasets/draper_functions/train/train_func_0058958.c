gwy_app_data_browser_shoot_object(GObject *button,
                                  GwyAppDataBrowser *browser)
{
    GwyAppDataProxy *proxy;
    GtkTreeView *treeview;
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    guint pageno;
    const gchar *action;

    g_return_if_fail(browser->current);

    action = g_object_get_data(button, "action");
    gwy_debug("action: %s", action);

    proxy = browser->current;
    pageno = browser->active_page;

    treeview = GTK_TREE_VIEW(browser->lists[pageno]);
    selection = gtk_tree_view_get_selection(treeview);
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        g_warning("Nothing is selected");
        return;
    }

    if (gwy_strequal(action, "delete"))
        gwy_app_data_browser_delete_object(proxy, pageno, model, &iter);
    else if (gwy_strequal(action, "duplicate"))
        gwy_app_data_browser_copy_object(proxy, pageno, model, &iter, proxy);
    else if (gwy_strequal(action, "extract"))
        gwy_app_data_browser_copy_object(proxy, pageno, model, &iter, NULL);
    else
        g_warning("Unknown action <%s>", action);
}
