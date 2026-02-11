entangle_auto_drawer_set_over(EntangleOverlayBox *ovBox,
                              GtkWidget *widget)
{
    EntangleAutoDrawer *drawer = ENTANGLE_AUTO_DRAWER(ovBox);
    EntangleAutoDrawerPrivate *priv = drawer->priv;
    GtkWidget *oldChild = gtk_bin_get_child(GTK_BIN(priv->evBox));

    if (oldChild) {
        g_object_ref(oldChild);
        gtk_container_remove(GTK_CONTAINER(priv->evBox), oldChild);
    }

    if (widget) {
        gtk_container_add(GTK_CONTAINER(priv->evBox), widget);
    }

    if (oldChild) {
        g_object_unref(oldChild);
    }

    priv->over = widget;
}
