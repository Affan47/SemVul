dh_util_font_add_web_view (WebKitWebView *view)
{
        static gboolean setup;

        if (!setup) {
                IgeConf *conf;

                conf = ige_conf_get ();

		ige_conf_notify_add (conf,
                                     DH_CONF_USE_SYSTEM_FONTS,
                                     font_notify_cb,
                                     NULL);
		ige_conf_notify_add (conf,
                                     DH_CONF_SYSTEM_VARIABLE_FONT,
                                     font_notify_cb,
                                     NULL);
		ige_conf_notify_add (conf,
                                     DH_CONF_SYSTEM_FIXED_FONT,
                                     font_notify_cb,
                                     NULL);
		ige_conf_notify_add (conf,
                                     DH_CONF_VARIABLE_FONT,
                                     font_notify_cb,
                                     NULL);
		ige_conf_notify_add (conf,
                                     DH_CONF_FIXED_FONT,
                                     font_notify_cb,
                                     NULL);

                setup = TRUE;
        }

        views = g_list_prepend (views, view);

        g_signal_connect (view, "destroy",
                          G_CALLBACK (view_destroy_cb),
                          NULL);

        view_setup_fonts (view);
}
