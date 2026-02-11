ibus_im_context_class_init (IBusIMContextClass *class)
{
    IDEBUG ("%s", __FUNCTION__);

    GtkIMContextClass *im_context_class = GTK_IM_CONTEXT_CLASS (class);
    GObjectClass *gobject_class = G_OBJECT_CLASS (class);

    parent_class = (GtkIMContextClass *) g_type_class_peek_parent (class);

    im_context_class->reset = ibus_im_context_reset;
    im_context_class->focus_in = ibus_im_context_focus_in;
    im_context_class->focus_out = ibus_im_context_focus_out;
    im_context_class->filter_keypress = ibus_im_context_filter_keypress;
    im_context_class->get_preedit_string = ibus_im_context_get_preedit_string;
    im_context_class->set_client_window = ibus_im_context_set_client_window;
    im_context_class->set_cursor_location = ibus_im_context_set_cursor_location;
    im_context_class->set_use_preedit = ibus_im_context_set_use_preedit;
    im_context_class->set_surrounding = ibus_im_context_set_surrounding;
    gobject_class->notify = ibus_im_context_notify;
    gobject_class->finalize = ibus_im_context_finalize;

    _signal_commit_id =
        g_signal_lookup ("commit", G_TYPE_FROM_CLASS (class));
    g_assert (_signal_commit_id != 0);

    _signal_preedit_changed_id =
        g_signal_lookup ("preedit-changed", G_TYPE_FROM_CLASS (class));
    g_assert (_signal_preedit_changed_id != 0);

    _signal_preedit_start_id =
        g_signal_lookup ("preedit-start", G_TYPE_FROM_CLASS (class));
    g_assert (_signal_preedit_start_id != 0);

    _signal_preedit_end_id =
        g_signal_lookup ("preedit-end", G_TYPE_FROM_CLASS (class));
    g_assert (_signal_preedit_end_id != 0);

    _signal_delete_surrounding_id =
        g_signal_lookup ("delete-surrounding", G_TYPE_FROM_CLASS (class));
    g_assert (_signal_delete_surrounding_id != 0);

    _signal_retrieve_surrounding_id =
        g_signal_lookup ("retrieve-surrounding", G_TYPE_FROM_CLASS (class));
    g_assert (_signal_retrieve_surrounding_id != 0);

    _use_key_snooper = !_get_boolean_env ("IBUS_DISABLE_SNOOPER",
                                          !(ENABLE_SNOOPER));
    _use_sync_mode = _get_boolean_env ("IBUS_ENABLE_SYNC_MODE", FALSE);


    if (_use_key_snooper) {

        const gchar * prgname = g_get_prgname ();
        if (g_getenv ("IBUS_NO_SNOOPER_APPS")) {
            _no_snooper_apps = g_getenv ("IBUS_NO_SNOOPER_APPS");
        }
        gchar **p;
        gchar ** apps = g_strsplit (_no_snooper_apps, ",", 0);
        for (p = apps; *p != NULL; p++) {
            if (g_regex_match_simple (*p, prgname, 0, 0)) {
                _use_key_snooper = FALSE;
                break;
            }
        }
        g_strfreev (apps);
    }


    if (_bus == NULL) {
        ibus_set_display (gdk_display_get_name (gdk_display_get_default ()));
        _bus = ibus_bus_new_async ();


        if (ibus_bus_is_connected (_bus)) {
            _create_fake_input_context ();
        }

        g_signal_connect (_bus, "connected", G_CALLBACK (_bus_connected_cb), NULL);
    }


    if (_key_snooper_id == 0) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        _key_snooper_id = gtk_key_snooper_install (_key_snooper_cb, NULL);
#pragma GCC diagnostic pop
    }

    _daemon_name_watch_id = g_bus_watch_name (G_BUS_TYPE_SESSION,
                                              IBUS_SERVICE_IBUS,
                                              G_BUS_NAME_WATCHER_FLAGS_NONE,
                                              daemon_name_appeared,
                                              daemon_name_vanished,
                                              NULL,
                                              NULL);
}
