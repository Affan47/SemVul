nemo_desktop_background_set_up_widget (NemoDesktopBackground *self)
{
	GdkWindow *window;
	gboolean in_fade = FALSE;
        GtkWidget *widget;

        widget = self->details->widget;

	if (!gtk_widget_get_realized (widget)) {
		return;
	}

	nemo_desktop_background_ensure_realized (self);
        window = gtk_layout_get_bin_window (GTK_LAYOUT (widget));

	in_fade = fade_to_surface (self, window,
				   self->details->background_surface);

	if (!in_fade) {
		cairo_pattern_t *pattern;

		pattern = cairo_pattern_create_for_surface (self->details->background_surface);
		gdk_window_set_background_pattern (window, pattern);
		cairo_pattern_destroy (pattern);

                gnome_bg_set_surface_as_root (gtk_widget_get_screen (widget),
                                              self->details->background_surface);
	}
}
