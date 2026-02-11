br_queue_dispose (GObject *object)
{
    BrQueue *self = (BrQueue *) object;
    BrQueuePrivate *priv = self->priv;

    if (priv->proxy) {
        dbus_g_proxy_disconnect_signal (priv->proxy, "UriAdded",
                                        G_CALLBACK (uri_added_cb), self);
        dbus_g_proxy_disconnect_signal (priv->proxy, "UriRemoved",
                                        G_CALLBACK (uri_removed_cb), self);
        dbus_g_proxy_disconnect_signal (priv->proxy, "ItemMoved",
                                        G_CALLBACK (item_moved_cb), self);
        dbus_g_proxy_disconnect_signal (priv->proxy, "IndexChanged",
                                        G_CALLBACK (index_changed_cb), self);
        dbus_g_proxy_disconnect_signal (priv->proxy, "PositionChanged",
                                        G_CALLBACK (position_changed_cb), self);
        dbus_g_proxy_disconnect_signal (priv->proxy, "StateChanged",
                                        G_CALLBACK (state_changed_cb), self);

        g_object_unref (priv->proxy);
        priv->proxy = NULL;
    }

    G_OBJECT_CLASS (br_queue_parent_class)->dispose (object);
}
