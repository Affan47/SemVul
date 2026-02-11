gupnp_context_new (GMainContext *main_context,
                   const char   *iface,
                   guint         port,
                   GError      **error)
{
        if (main_context)
                g_warning ("gupnp_context_new::main_context is deprecated."
                           " Use g_main_context_push_thread_default()"
                           " instead");

        return g_initable_new (GUPNP_TYPE_CONTEXT,
                               NULL,
                               error,
                               "interface", iface,
                               "port", port,
                               NULL);
}
