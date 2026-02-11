parse_data (GUPnPMediaCollection *collection, const char *data)
{
        GUPnPDIDLLiteParser *parser;
        GError *error = NULL;
        gboolean result;

        parser = gupnp_didl_lite_parser_new ();
        g_signal_connect_swapped (G_OBJECT (parser),
                                  "container-available",
                                  G_CALLBACK (on_container_available),
                                  collection);
        g_signal_connect_swapped (G_OBJECT (parser),
                                  "item-available",
                                  G_CALLBACK (on_item_available),
                                  collection);

        result = gupnp_didl_lite_parser_parse_didl_recursive (parser,
                                                              data,
                                                              TRUE,
                                                              &error);
        if (!result) {
                GUPnPMediaCollectionPrivate *priv = collection->priv;

                g_warning ("Failed to parse DIDL-Lite: %s", error->message);
                g_error_free (error);
                if (priv->container) {
                        g_object_unref (priv->container);
                        priv->container = NULL;
                }
                if (priv->items) {
                        g_list_free_full (priv->items, g_object_unref);
                        priv->items = NULL;
                }
        }
}
