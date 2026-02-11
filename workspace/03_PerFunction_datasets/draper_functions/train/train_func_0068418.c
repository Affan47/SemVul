nautilus_disc_burn_get_location_widget (NautilusLocationWidgetProvider *iface,
                                        const char                     *uri,
                                        GtkWidget                      *window)
{
        if (g_str_has_prefix (uri, "burn:")) {
                GtkWidget    *bar;
                NautilusDiscBurn *burn;

                DEBUG_PRINT ("Get location widget for burn\n");

                burn = NAUTILUS_DISC_BURN (iface);

                bar = nautilus_disc_burn_bar_new ();
		nautilus_disc_burn_bar_set_title (NAUTILUS_DISC_BURN_BAR (bar),
		                                  burn->priv->title);
		nautilus_disc_burn_bar_set_icon (NAUTILUS_DISC_BURN_BAR (bar),
		                                 burn->priv->icon);
                sense_widget (burn, nautilus_disc_burn_bar_get_button (NAUTILUS_DISC_BURN_BAR (bar)));

                g_signal_connect (bar, "activate",
                                  G_CALLBACK (bar_activated_cb),
                                  burn);
		g_signal_connect (bar, "title-changed",
		                  G_CALLBACK (title_changed_cb),
		                  burn);
		g_signal_connect (bar, "icon-changed",
		                  G_CALLBACK (icon_changed_cb),
		                  burn);

                gtk_widget_show (bar);

                return bar;
        }

        return NULL;
}
