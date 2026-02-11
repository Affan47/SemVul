gdl_dock_placeholder_destroy (GtkObject *object)
{
    GdlDockPlaceholder *ph = GDL_DOCK_PLACEHOLDER (object);

    if (ph->_priv) {
        if (ph->_priv->host)
            gdl_dock_placeholder_detach (GDL_DOCK_OBJECT (object), FALSE);
        g_free (ph->_priv);
        ph->_priv = NULL;
    }

    GDL_CALL_PARENT (GTK_OBJECT_CLASS, destroy, (object));
}
