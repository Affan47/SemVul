zoom_changed(GtkRadioButton *button,
             ControlsType *controls)
{
    ZoomType zoom_mode = gwy_radio_buttons_get_current(controls->zoom);
    gchar key[32];

    if (button && zoom_mode == controls->zoom_mode)
        return;

    controls->zoom_mode = zoom_mode;
    if (controls->prev_mode != PREV_FFT)
        return;

    g_snprintf(key, sizeof(key), "/zoomed/%u", zoom_mode);
    gwy_pixmap_layer_set_data_key(controls->view_layer, key);

    g_snprintf(key, sizeof(key), "/zoomed-mask/%u", zoom_mode);
    gwy_pixmap_layer_set_data_key(controls->mask_layer, key);

    gwy_set_data_preview_size(GWY_DATA_VIEW(controls->view), PREVIEW_SIZE);
}
