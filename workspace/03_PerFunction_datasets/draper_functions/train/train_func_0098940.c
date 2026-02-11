square_changed(GtkWidget *check,
               CalibrateControls *controls)
{
    CalibrateArgs *args = controls->args;

    if (controls->in_update)
        return;

    controls->in_update = TRUE;

    args->square
        = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check));
    if (args->square) {
        args->yreal = args->xreal/args->xres * args->yres;
        args->yratio = args->yreal/args->yorig;
    }
    calibrate_dialog_update(controls, args);
    controls->in_update = FALSE;
}
