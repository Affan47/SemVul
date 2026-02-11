gdl_dock_destroy (GtkObject *object)
{
    GdlDock *dock = GDL_DOCK (object);

    if (dock->_priv) {
        GdlDockPrivate *priv = dock->_priv;
        dock->_priv = NULL;

        if (priv->window) {
            gtk_widget_destroy (priv->window);
            priv->floating = FALSE;
            priv->window = NULL;
        }


        if (priv->xor_gc) {
            g_object_unref (priv->xor_gc);
            priv->xor_gc = NULL;
        }

        g_free (priv);
    }

    GDL_CALL_PARENT (GTK_OBJECT_CLASS, destroy, (object));
}
