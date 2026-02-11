gx_tuner_init (GxTuner *tuner) {
    g_assert(GX_IS_TUNER(tuner));
    tuner->freq = 0;
    tuner->reference_pitch = 440.0;
    GtkWidget *widget = GTK_WIDGET(tuner);
    widget->requisition.width = tuner_width;
    widget->requisition.height = tuner_height;
}
