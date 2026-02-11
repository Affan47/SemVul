do_update_control_entry(GtkWidget *widget,
                                    GdkEventFocus *ev G_GNUC_UNUSED,
                                    gpointer data)
{
    g_return_if_fail(ENTANGLE_IS_CONTROL_PANEL(data));

    EntangleControlText *control = g_object_get_data(G_OBJECT(widget), "control");
    EntangleControlPanel *panel = ENTANGLE_CONTROL_PANEL(data);
    EntangleControlPanelPrivate *priv = panel->priv;
    const char *text;

    text = gtk_entry_get_text(GTK_ENTRY(widget));

    ENTANGLE_DEBUG("entry [%s]", text);
    g_object_set(control, "value", text, NULL);

    entangle_camera_save_controls_async(priv->camera,
                                        NULL,
                                        do_update_control_finish,
                                        panel);
}
