draw_check (GtkStyle      *style,
	    GdkWindow     *window,
	    GtkStateType   state_type,
	    GtkShadowType  shadow_type,
	    GdkRectangle  *area,
	    GtkWidget     *widget,
	    const gchar   *detail,
	    gint           x,
	    gint           y,
	    gint           width,
	    gint           height)
{
  BluecurveStyle *bluecurve_style = BLUECURVE_STYLE (style);
  GdkGC *gc = style->base_gc[state_type];
  GdkPixmap *pixmap;

  if (DETAIL ("check"))
    {
      parent_class->draw_check (style, window, state_type, shadow_type, area,
				 widget, detail, x, y, width, height);
      return;
    }

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  if (shadow_type == GTK_SHADOW_IN)
    pixmap = bluecurve_style->check_pixmap_active[state_type];
  else if (shadow_type == GTK_SHADOW_ETCHED_IN)
    pixmap = bluecurve_style->check_pixmap_inconsistent[state_type];
  else
    pixmap = bluecurve_style->check_pixmap_nonactive[state_type];

  x += (width - CHECK_SIZE)/2;
  y += (height - CHECK_SIZE)/2;

  gdk_draw_drawable (window, gc,
		     pixmap,
		     0, 0,
		     x, y,
		     CHECK_SIZE, CHECK_SIZE);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}
