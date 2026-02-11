get_metadata_browser(GwyContainer *data,
                     BrowserDataType type,
                     gint id)
{
    MetadataBrowser *browser;

    g_return_val_if_fail(GWY_IS_CONTAINER(data), NULL);
    g_return_val_if_fail(id >= 0, NULL);
    if ((browser = gwy_meta_switch_data(NULL, data, type, id))) {
        gtk_window_present(GTK_WINDOW(browser->window));
        return browser->window;
    }
    browser = metadata_browser_new();
    gwy_meta_switch_data(browser, data, type, id);
    gtk_widget_show_all(browser->window);
    return browser->window;
}
