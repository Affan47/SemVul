moblin_netbook_draw_expander (GtkStyle         *style,
                              GdkWindow        *window,
                              GtkStateType      state_type,
                              GdkRectangle     *area,
                              GtkWidget        *widget,
                              const gchar      *detail,
                              gint              x,
                              gint              y,
                              GtkExpanderStyle  expander_style)
{
  cairo_t *cr;

  cr = moblin_netbook_cairo_create (window, area);

  x -= 6;
  y -= 6;


  cairo_set_source_rgba (cr, 0.6, 0.6, 0.6, 0.6);
  moblin_netbook_rounded_rectangle (cr, x, y, 12, 12, 2 );
  cairo_stroke_preserve (cr);

  if (state_type == GTK_STATE_PRELIGHT || state_type == GTK_STATE_ACTIVE)
    cairo_set_source_rgba (cr, 0, 0.6, 0.8, 1);
  else
    cairo_set_source_rgba (cr, 1, 1, 1, 1);

  cairo_fill (cr);

  if (state_type == GTK_STATE_PRELIGHT || state_type == GTK_STATE_ACTIVE)
    cairo_set_source_rgba (cr, 1, 1, 1, 1);
  else
    cairo_set_source_rgba (cr, 0, 0.6, 0.8, 1);

  cairo_move_to (cr, x + 2, y + 6);
  cairo_line_to (cr, x + 10, y + 6);
  cairo_stroke (cr);

  if (expander_style != GTK_EXPANDER_EXPANDED)
    {
      if (expander_style == GTK_EXPANDER_SEMI_COLLAPSED
          || expander_style == GTK_EXPANDER_SEMI_EXPANDED)
        {
          if (state_type == GTK_STATE_PRELIGHT
              || state_type == GTK_STATE_ACTIVE)
            cairo_set_source_rgba (cr, 1, 1, 1, 0.5);
          else
            cairo_set_source_rgba (cr, 0, 0.6, 0.8, 0.5);
        }

      cairo_move_to (cr, x + 6, y + 2);
      cairo_line_to (cr, x + 6, y + 10);
      cairo_stroke (cr);
    }

  cairo_destroy (cr);
}
