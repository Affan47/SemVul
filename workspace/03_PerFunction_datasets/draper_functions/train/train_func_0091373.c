webx_preview_nav_popup_realize (GtkWidget       *widget,
                                WebxPreview     *preview)
{
  if (! preview->nav_gc)
    {
      preview->nav_gc = gdk_gc_new (widget->window);

      gdk_gc_set_function (preview->nav_gc, GDK_INVERT);
      gdk_gc_set_line_attributes (preview->nav_gc,
                                  WEBX_NAV_PEN_WIDTH,
                                  GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_ROUND);
    }
}
