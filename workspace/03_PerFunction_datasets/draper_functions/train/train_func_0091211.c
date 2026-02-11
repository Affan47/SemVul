pixmap_load_update_values(PixmapLoadControls *controls,
                          PixmapLoadArgs *args)
{
    GtkAdjustment *adj;

    adj = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(controls->xreal));
    args->xreal = gtk_adjustment_get_value(adj);
    adj = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(controls->yreal));
    args->yreal = gtk_adjustment_get_value(adj);
    args->xyexponent
        = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(controls->xyexponent));
    adj = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(controls->zreal));
    args->zreal = gtk_adjustment_get_value(adj);
    args->zexponent
        = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(controls->zexponent));
    if (controls->maptype)
        args->maptype
            = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(controls->maptype));
}
