gtkpod_warning(gchar* message, ...) {
    g_return_if_fail (GTKPOD_IS_APP(gtkpod_app));
    gchar* msg;
    va_list args;
    va_start (args, message);
    msg = g_strdup_vprintf(message, args);
    va_end (args);

    GTKPOD_APP_GET_INTERFACE (gtkpod_app)->gtkpod_warning(gtkpod_app, "%s", msg);
    g_free(msg);
}
