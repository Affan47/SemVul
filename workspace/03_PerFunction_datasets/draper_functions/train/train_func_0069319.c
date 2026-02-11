tilt_dx_changed(GtkAdjustment *adj,
                TiltControls *controls)
{
    TiltArgs *args = controls->args;

    if (controls->in_update)
        return;

    args->dx = gtk_adjustment_get_value(adj);
    tilt_deriv_to_angles(controls);
}
