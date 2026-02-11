gvir_log_handler(const gchar *log_domain G_GNUC_UNUSED,
                             GLogLevelFlags log_level G_GNUC_UNUSED,
                             const gchar *message,
                             gpointer user_data)
{
    if (user_data)
        fprintf(stderr, "%s\n", message);
}
