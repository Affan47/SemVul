create_layout_with_attrs (GtkWidget *widget,
                          const GdkRectangle *cell_area,
                          GdTwoLinesRenderer *self,
                          PangoEllipsizeMode ellipsize)
{
  PangoLayout *layout;
  gint wrap_width, xpad;
  PangoWrapMode wrap_mode;
  PangoAlignment alignment;

  g_object_get (self,
                "wrap-width", &wrap_width,
                "wrap-mode", &wrap_mode,
                "alignment", &alignment,
                "xpad", &xpad,
                NULL);

  layout = pango_layout_new (gtk_widget_get_pango_context (widget));

  pango_layout_set_ellipsize (layout, ellipsize);
  pango_layout_set_alignment (layout, alignment);

  if (wrap_width != -1)
    {
      pango_layout_set_width (layout, wrap_width * PANGO_SCALE);
      pango_layout_set_wrap (layout, wrap_mode);
    }
  else
    {
      if (cell_area != NULL)
        pango_layout_set_width (layout, (cell_area->width - 2 * xpad) * PANGO_SCALE);
      else
        pango_layout_set_width (layout, -1);

      pango_layout_set_wrap (layout, PANGO_WRAP_CHAR);
    }

  return layout;
}
