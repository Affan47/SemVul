gs_grab_mouse_reset (GSGrab *grab)
{
        if (grab->priv->mouse_grab_window != NULL) {
                g_object_remove_weak_pointer (G_OBJECT (grab->priv->mouse_grab_window),
                                              (gpointer *) &grab->priv->mouse_grab_window);
        }

        grab->priv->mouse_grab_window = NULL;
        grab->priv->mouse_grab_screen = NULL;
}
