gwy_meta_destroy(MetadataBrowser *browser)
{
    gwy_signal_handler_disconnect(browser->meta, browser->changed_id);
    g_object_set_data(G_OBJECT(browser->meta), "metadata-browser", NULL);
    g_object_weak_unref(G_OBJECT(browser->meta),
                        (GWeakNotify)&gwy_meta_data_finalized,
                        browser);
    g_free(browser);
}
