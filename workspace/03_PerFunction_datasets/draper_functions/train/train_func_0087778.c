setup_logging(void)
{
    const gchar *domains[] = {
        "GLib", "GLib-GObject", "GLib-GIO", "GModule", "GThread",
        "GdkPixbuf", "Gdk", "Gtk",
        "GdkGLExt", "GtkGLExt",
        "Pango", "Unique",
        "Gwyddion", "GwyProcess", "GwyDraw", "Gwydgets", "GwyModule", "GwyApp",
        "Module", NULL
    };
    gchar *log_filename;
    gsize i;
    FILE *logfile;

    log_filename = gwy_app_settings_get_log_filename();
    logfile = g_fopen(log_filename, "w");
    for (i = 0; i < G_N_ELEMENTS(domains); i++)
        g_log_set_handler(domains[i],
                          G_LOG_LEVEL_DEBUG | G_LOG_LEVEL_MESSAGE
                          | G_LOG_LEVEL_INFO | G_LOG_LEVEL_WARNING,
                          logger, logfile);
}
