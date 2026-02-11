gwy_3d_window_set_mode(gpointer userdata, GtkWidget *button)
{
    Gwy3DWindow *gwy3dwindow;
    Gwy3DMovement movement;

    if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
        return;

    gwy3dwindow = (Gwy3DWindow*)g_object_get_data(G_OBJECT(button),
                                                  "gwy3dwindow");
    g_return_if_fail(GWY_IS_3D_WINDOW(gwy3dwindow));
    if (gwy3dwindow->in_update)
        return;

    gwy3dwindow->in_update = TRUE;
    movement = GPOINTER_TO_INT(userdata);
    gtk_toggle_button_set_active
        (GTK_TOGGLE_BUTTON(gwy3dwindow->buttons[movement]), TRUE);
    gtk_toggle_button_set_active
        (GTK_TOGGLE_BUTTON(gwy3dwindow->buttons[movement + N_BUTTONS]), TRUE);

    gwy_3d_view_set_movement_type(GWY_3D_VIEW(gwy3dwindow->gwy3dview),
                                  movement);
    gwy3dwindow->in_update = FALSE;
}
