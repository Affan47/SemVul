clutter_text_get_preferred_height (ClutterActor *self,
                                   gfloat        for_width,
                                   gfloat       *min_height_p,
                                   gfloat       *natural_height_p)
{
  ClutterTextPrivate *priv = CLUTTER_TEXT (self)->priv;

  if (for_width == 0)
    {
      if (min_height_p)
        *min_height_p = 0;

      if (natural_height_p)
        *natural_height_p = 0;
    }
  else
    {
      PangoLayout *layout;
      PangoRectangle logical_rect = { 0, };
      gint logical_height;
      gfloat layout_height;

      if (priv->single_line_mode)
        for_width = -1;

      layout = clutter_text_create_layout (CLUTTER_TEXT (self),
                                           for_width, -1);

      pango_layout_get_extents (layout, NULL, &logical_rect);


      logical_height = logical_rect.y + logical_rect.height;
      layout_height = ceilf (logical_height / 1024.0f);

      if (min_height_p)
        {


          if ((priv->ellipsize && priv->wrap) && !priv->single_line_mode)
            {
              PangoLayoutLine *line;
              gfloat line_height;

              line = pango_layout_get_line_readonly (layout, 0);
              pango_layout_line_get_extents (line, NULL, &logical_rect);

              logical_height = logical_rect.y + logical_rect.height;
              line_height = ceilf (logical_height / 1024.0f);

              *min_height_p = line_height;
            }
          else
            *min_height_p = layout_height;
        }

      if (natural_height_p)
        *natural_height_p = layout_height;
    }
}
