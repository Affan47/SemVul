gva_get_debug_flags (void)
{
        static guint flags = G_MAXUINT;

        if (G_UNLIKELY (flags == G_MAXUINT))
        {
                static const GDebugKey debug_keys[] =
                {
                        { "mame",  GVA_DEBUG_MAME },
                        { "sql",   GVA_DEBUG_SQL },
                        { "io",    GVA_DEBUG_IO },
                        { "inp",   GVA_DEBUG_INP },
                        { "gst",   GVA_DEBUG_GST },
                        { "http",  GVA_DEBUG_HTTP }
                };

                const gchar *env = g_getenv ("GVA_DEBUG");
                gint ii;

                for (ii = 0; ii < G_N_ELEMENTS (debug_keys); ii++)
                {
                        gchar *all_caps;

                        all_caps = g_ascii_strup (debug_keys[ii].key, -1);

                        g_log_set_handler (
                                G_LOG_DOMAIN, debug_keys[ii].value,
                                (GLogFunc) log_handler, all_caps);

                        g_free (all_caps);
                }

                flags = g_parse_debug_string (
                        (env != NULL) ? env : "", debug_keys,
                        G_N_ELEMENTS (debug_keys));
        }

        return (GvaDebugFlags) flags;
}
