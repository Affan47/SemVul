equinox_style_draw_vline (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail, gint y1, gint y2, gint x) {
	EquinoxStyle *equinox_style = EQUINOX_STYLE (style);
	EquinoxColors *colors = &equinox_style->colors;
	cairo_t *cr = equinox_begin_paint (window, area);

	SeparatorParameters separator;
	WidgetParameters params;
	separator.horizontal = FALSE;
	if (widget && widget->parent) {
		separator.inToolbar = EQUINOX_IS_TOOLBAR (widget->parent);
	} else {
		separator.inToolbar = FALSE;
	}
	equinox_set_widget_parameters (widget, style, state_type, &params);


	if (widget && widget->parent && widget->parent->parent && widget->parent->parent->parent &&
      EQUINOX_IS_HBOX (widget->parent) &&
      EQUINOX_IS_TOGGLE_BUTTON (widget->parent->parent) &&
      EQUINOX_IS_COMBO_BOX (widget->parent->parent->parent)) {
	}
	else


	cairo_destroy (cr);
}
