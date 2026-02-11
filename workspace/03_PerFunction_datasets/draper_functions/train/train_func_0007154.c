read_enable_event_sounds(ca_context *c, GtkSettings *s) {
        gboolean enable_event_sounds = TRUE;

        if (!g_getenv("CANBERRA_FORCE_EVENT_SOUNDS"))
                g_object_get(G_OBJECT(s), "gtk-enable-event-sounds", &enable_event_sounds, NULL);

        ca_context_change_props(c, CA_PROP_CANBERRA_ENABLE, enable_event_sounds ? "1" : "0", NULL);
}
