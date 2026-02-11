_gnome_settings_profile_log (const char *func,
                             const char *note,
                             const char *format,
                             ...)
{
        va_list args;
        char   *str;
        char   *formatted;

        if (format == NULL) {
                formatted = g_strdup ("");
        } else {
                va_start (args, format);
                formatted = g_strdup_vprintf (format, args);
                va_end (args);
        }

        if (func != NULL) {
                str = g_strdup_printf ("MARK: %s %s: %s %s", g_get_prgname(), func, note ? note : "", formatted);
        } else {
                str = g_strdup_printf ("MARK: %s: %s %s", g_get_prgname(), note ? note : "", formatted);
        }

        g_free (formatted);

        g_access (str, F_OK);
        g_free (str);
}
