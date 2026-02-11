nautilus_desktop_background_constructed (GObject *obj)
{
        NautilusDesktopBackground *self;
        GtkWidget *widget;

        self = NAUTILUS_DESKTOP_BACKGROUND (obj);

        if (G_OBJECT_CLASS (nautilus_desktop_background_parent_class)->constructed != NULL) {
                G_OBJECT_CLASS (nautilus_desktop_background_parent_class)->constructed (obj);
        }

        widget = self->details->widget;

        g_assert (widget != NULL);

 	g_signal_connect_object (widget, "destroy",
                                 G_CALLBACK (on_widget_destroyed), self, 0);
	g_signal_connect_object (widget, "realize",
				 G_CALLBACK (widget_realize_cb), self, 0);
	g_signal_connect_object (widget, "unrealize",
				 G_CALLBACK (widget_unrealize_cb), self, 0);

        gnome_bg_load_from_preferences (self->details->bg,
                                        gnome_background_preferences);


        g_signal_connect (gnome_background_preferences,
                          "change-event",
                          G_CALLBACK (background_settings_change_event_cb),
                          self);

	queue_background_change (self);
}
