moblin_netbook_draw_option (GtkStyle     *style,
                            GdkWindow    *window,
                            GtkStateType  state_type,
                            GtkShadowType shadow_type,
                            GdkRectangle *area,
                            GtkWidget    *widget,
                            const gchar  *detail,
                            gint          x,
                            gint          y,
                            gint          width,
                            gint          height)
{
  cairo_t *cr;
  gint cx, cy, radius;

  DEBUG;

  cr = moblin_netbook_cairo_create (window, area);

  cairo_set_line_width (cr, 1);
  cairo_translate (cr, 0.5, 0.5);
  width--;
  height--;

  if (shadow_type == GTK_SHADOW_IN && state_type != GTK_STATE_INSENSITIVE)
    {
      state_type = GTK_STATE_SELECTED;
    }


  if (width % 2) width--;
  radius = width / 2;
  cx = x + radius;
  cy = y + radius;


  gdk_cairo_set_source_color (cr, &style->base[state_type]);
  cairo_arc (cr, cx, cy, radius, 0, M_PI * 2);
  cairo_fill (cr);


  cairo_arc (cr, cx, cy, radius, 0, M_PI * 2);
  moblin_netbook_set_border_color (cr, style, state_type);
  cairo_stroke (cr);


  if (shadow_type == GTK_SHADOW_IN)
    {
      cairo_arc (cr, cx, cy, radius - 4,  0, M_PI * 2);
      gdk_cairo_set_source_color (cr, &style->text[state_type]);
      cairo_fill (cr);
    }
  cairo_destroy (cr);
}
