gs_lock_plug_style_set (GtkWidget *widget,
                        GtkStyle  *previous_style)
{
        GSLockPlug *plug;

        if (GTK_WIDGET_CLASS (gs_lock_plug_parent_class)->style_set) {
                GTK_WIDGET_CLASS (gs_lock_plug_parent_class)->style_set (widget, previous_style);
        }

        plug = GS_LOCK_PLUG (widget);

        gtk_container_set_border_width (GTK_CONTAINER (plug->priv->vbox), 24);
        gtk_box_set_spacing (GTK_BOX (plug->priv->vbox), 12);

        gtk_container_set_border_width (GTK_CONTAINER (plug->priv->auth_action_area), 0);
        gtk_box_set_spacing (GTK_BOX (plug->priv->auth_action_area), 5);
}
