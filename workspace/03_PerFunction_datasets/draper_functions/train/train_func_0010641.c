do_camera_select(GtkTreeSelection *sel, EntangleCameraPicker *picker)
{
    g_return_if_fail(ENTANGLE_IS_CAMERA_PICKER(picker));

    EntangleCameraPickerPrivate *priv = picker->priv;
    GtkWidget *connect;
    GtkTreeIter iter;
    gboolean selected;

    ENTANGLE_DEBUG("selection changed");

    connect = GTK_WIDGET(gtk_builder_get_object(priv->builder, "picker-connect"));

    selected = gtk_tree_selection_get_selected(sel, NULL, &iter);
    gtk_widget_set_sensitive(connect, selected);
}
