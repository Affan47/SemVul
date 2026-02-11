bintext_changed_cb(G_GNUC_UNUSED GtkWidget *button,
                   RawFileControls *controls)
{
    rawfile_warn_clear(controls);
    if (!controls->in_update) {
        update_dialog_values(controls);
        update_dialog_controls(controls);
    }
}
