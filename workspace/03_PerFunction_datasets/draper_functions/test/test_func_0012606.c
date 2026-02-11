gdl_dock_reduce (GdlDockObject *object)
{
    GdlDock *dock = GDL_DOCK (object);
    GtkWidget *parent;

    if (dock->priv->root)
        return;

    if (gdl_dock_object_is_automatic (GDL_DOCK_OBJECT (dock))) {
        gtk_widget_destroy (GTK_WIDGET (dock));

    } else if (gdl_dock_object_is_closed (GDL_DOCK_OBJECT (dock))) {

        if (dock->priv->floating)
            gtk_widget_hide (GTK_WIDGET (dock));
        else {
            GtkWidget *widget = GTK_WIDGET (object);
            parent = gtk_widget_get_parent (widget);
            if (parent)
                gtk_container_remove (GTK_CONTAINER (parent), widget);
        }
    }
}
