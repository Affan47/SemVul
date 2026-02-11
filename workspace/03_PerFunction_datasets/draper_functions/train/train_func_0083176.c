proportional_changed_cb(GtkToggleButton *check_button,
                        ScaleArgs *args)
{
    ScaleControls *controls;

    controls = g_object_get_data(G_OBJECT(check_button), "controls");
    if (controls->in_update)
        return;

    controls->in_update = TRUE;
    args->proportional = gtk_toggle_button_get_active(check_button);
    if (args->proportional) {
        args->xres = GWY_ROUND(args->ratio*args->org_xres);
        args->yres = GWY_ROUND(args->ratio*args->org_yres);
    }
    scale_dialog_update(controls, args);
    controls->in_update = FALSE;
}
