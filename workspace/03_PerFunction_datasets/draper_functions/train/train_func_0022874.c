log_handler (const gchar *log_domain,
             GLogLevelFlags log_level,
             const gchar *message,
             const gchar *log_level_id)
{
        if ((gva_get_debug_flags () & log_level) != 0)
                g_print (
                        "%s-LOG-DEBUG-%s: %s\n",
                        log_domain, log_level_id, message);
}
