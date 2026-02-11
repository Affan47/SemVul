book_tree_finalize (GObject *object)
{
        DhBookTreePriv *priv = GET_PRIVATE (object);


        if (g_signal_handler_is_connected (priv->book_manager, priv->book_created_id))
                g_signal_handler_disconnect (priv->book_manager, priv->book_created_id);
        if (g_signal_handler_is_connected (priv->book_manager, priv->book_deleted_id))
                g_signal_handler_disconnect (priv->book_manager, priv->book_deleted_id);
        if (g_signal_handler_is_connected (priv->book_manager, priv->book_enabled_id))
                g_signal_handler_disconnect (priv->book_manager, priv->book_enabled_id);
        if (g_signal_handler_is_connected (priv->book_manager, priv->book_disabled_id))
                g_signal_handler_disconnect (priv->book_manager, priv->book_disabled_id);
        if (g_signal_handler_is_connected (priv->book_manager, priv->group_by_language_id))
                g_signal_handler_disconnect (priv->book_manager, priv->group_by_language_id);

        g_object_unref (priv->store);
        g_object_unref (priv->book_manager);

        G_OBJECT_CLASS (dh_book_tree_parent_class)->finalize (object);
}
