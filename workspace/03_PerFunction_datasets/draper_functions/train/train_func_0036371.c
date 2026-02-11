draw_option (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x, gint y, gint width, gint height) {

  if (DETAIL ("option")) {
    if (shadow_type == GTK_SHADOW_IN) {
      gdk_draw_arc (window, style->fg_gc[state_type], TRUE,
		    x + 2, y + 2, width / 2, height / 2, 0, 360 * 64);
      gdk_draw_arc (window, style->fg_gc[state_type], FALSE,
		    x + 2, y + 2, width / 2, height / 2, 0, 360 * 64);
    }
  } else {
    gdk_draw_arc (window, style->base_gc[state_type],
		  TRUE, x, y, width, height, 0, 360 * 64);
    gdk_draw_arc (window, style->mid_gc[GTK_STATE_NORMAL], FALSE,
		  x, y, width, height, 45 * 64, 225 * 64);
    gdk_draw_arc (window, style->light_gc[GTK_STATE_NORMAL], FALSE,
		  x, y, width, height, 225 * 64, 180 * 64);
    if (shadow_type == GTK_SHADOW_IN) {
      gdk_draw_arc (window, style->text_gc[state_type], TRUE,
		    x + width / 4,
		    y + height / 4,
		    width / 2 + 1, height / 2 + 1,
		    0, 360 * 64);
      gdk_draw_arc (window, style->mid_gc[state_type], FALSE,
		    x + width / 4,
		    y + height / 4,
		    width / 2 + 1, height / 2 + 1,
		    0, 360 * 64);
    }
  }
}
