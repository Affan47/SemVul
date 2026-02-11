button_event(GtkWidget *widget, GdkEventButton *button)
{
    VncDisplayPrivate *priv = VNC_DISPLAY(widget)->priv;
    int n;

    if (priv->conn == NULL || !vnc_connection_is_initialized(priv->conn))
        return FALSE;

    if (priv->read_only)
        return FALSE;

    gtk_widget_grab_focus (widget);

    if (priv->grab_pointer && !priv->absolute && !priv->in_pointer_grab &&
        button->button == 1 && button->type == GDK_BUTTON_PRESS)
        do_pointer_grab(VNC_DISPLAY(widget), FALSE);

    n = 1 << (button->button - 1);
    if (button->type == GDK_BUTTON_PRESS)
        priv->button_mask |= n;
    else if (button->type == GDK_BUTTON_RELEASE)
        priv->button_mask &= ~n;

    if (priv->absolute) {
        vnc_connection_pointer_event(priv->conn, priv->button_mask,
                                     priv->last_x, priv->last_y);
    } else {
        vnc_connection_pointer_event(priv->conn, priv->button_mask,
                                     0x7FFF, 0x7FFF);
    }

    return TRUE;
}
