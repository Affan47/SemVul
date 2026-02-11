gtkpod_get_current_itdb() {
    g_return_val_if_fail (GTKPOD_IS_APP(gtkpod_app), NULL);
    return GTKPOD_APP_GET_INTERFACE (gtkpod_app)->current_itdb;
}
