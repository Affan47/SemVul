adwaita_draw_box (GtkStyle * style,
                  GdkWindow * window,
                  GtkStateType state_type,
                  GtkShadowType shadow_type,
                  GdkRectangle * area,
                  GtkWidget * widget,
                  const gchar * detail,
                  gint x,
                  gint y,
                  gint width,
                  gint height)
{
  if (GTK_IS_MENU (widget) &&
      g_strcmp0 (detail, "menu") == 0 &&
      wm_is_fallback ())
    {
      cairo_t *cr = drawable_to_cairo (window, area);
      cairo_pattern_t *pattern = cairo_pattern_create_linear (x, y, x, y + height);
      gdouble stop_1, stop_2, stop_3;

      stop_1 = MIN (1.0, 6.0 / (gdouble) height);
      stop_2 = MAX (stop_1, 0.33);
      stop_3 = MAX (stop_2, 0.66);

      cairo_pattern_add_color_stop_rgba (pattern, 0.0, 0.66, 0.66, 0.66, 0.0);
      cairo_pattern_add_color_stop_rgba (pattern, stop_1, 0.66, 0.66, 0.66, 0.25);
      cairo_pattern_add_color_stop_rgba (pattern, stop_2, 0.66, 0.66, 0.66, 0.80);
      cairo_pattern_add_color_stop_rgba (pattern, stop_3, 0.66, 0.66, 0.66, 1.0);
      cairo_pattern_add_color_stop_rgba (pattern, 1.0, 0.66, 0.66, 0.66, 1.0);
      cairo_pattern_set_extend (pattern, CAIRO_EXTEND_REPEAT);

      cairo_set_source (cr, pattern);
      cairo_rectangle (cr, x, y, width, height);
      cairo_stroke (cr);

      cairo_destroy (cr);
      cairo_pattern_destroy (pattern);
    }
  else
    {
      GTK_STYLE_CLASS (adwaita_style_parent_class)->draw_box (style, window, state_type, shadow_type,
                                                              area, widget, detail,
                                                              x, y, width, height);
    }
}
