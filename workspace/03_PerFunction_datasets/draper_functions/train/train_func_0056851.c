moblin_netbook_set_border_color (cairo_t     *cr,
                                 GtkStyle    *style,
                                 GtkStateType state)
{
  if (MOBLIN_NETBOOK_STYLE (style)->border_color)
    gdk_cairo_set_source_color (cr,
                                &(MOBLIN_NETBOOK_STYLE (style)->border_color[
                                    state]));
}
