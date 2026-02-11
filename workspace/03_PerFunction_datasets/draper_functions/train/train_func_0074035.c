same_resolution_changed(GtkToggleButton *button,
                        TipBlindControls *controls)
{
    TipBlindArgs *args;

    args = controls->args;
    args->same_resolution
        = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));

    if (!args->same_resolution)
        return;

    controls->in_update = TRUE;
    gtk_adjustment_set_value(GTK_ADJUSTMENT(controls->yres), args->xres);
    controls->in_update = FALSE;

    tip_update(controls);
}
