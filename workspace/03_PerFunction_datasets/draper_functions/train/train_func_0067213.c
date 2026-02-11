dispose (GObject *object)
{
    SoupCutClientPrivate *priv = SOUPCUT_CLIENT_GET_PRIVATE(object);

    if (priv->base) {
        soup_uri_free(priv->base);
        priv->base = NULL;
    }

    if (priv->messages) {
        g_list_foreach(priv->messages, (GFunc)g_object_unref, NULL);
        g_list_free(priv->messages);
        priv->messages = NULL;
    }

    if (priv->main_context) {
        g_main_context_unref(priv->main_context);
        priv->main_context = NULL;
    }

    if (priv->session) {
        g_object_unref(priv->session);
        priv->session = NULL;
    }

    G_OBJECT_CLASS(soupcut_client_parent_class)->dispose(object);
}
