paint_background_image_shadow_to_cairo_context (StThemeNode     *node,
                                                StShadow        *shadow_spec,
                                                cairo_pattern_t *pattern,
                                                cairo_t         *cr,
                                                cairo_path_t    *interior_path,
                                                cairo_path_t    *outline_path,
                                                int              x,
                                                int              y,
                                                int              width,
                                                int              height)
{
  cairo_pattern_t *shadow_pattern;

  g_assert (shadow_spec != NULL);
  g_assert (pattern != NULL);

  if (outline_path != NULL)
    {
      cairo_surface_t *clipped_surface;
      cairo_pattern_t *clipped_pattern;
      cairo_t *temp_cr;


      clipped_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
      temp_cr = cairo_create (clipped_surface);

      cairo_set_operator (temp_cr, CAIRO_OPERATOR_CLEAR);
      cairo_paint (temp_cr);
      cairo_set_operator (temp_cr, CAIRO_OPERATOR_SOURCE);

      if (interior_path != NULL)
        {
          cairo_append_path (temp_cr, interior_path);
          cairo_clip (temp_cr);
        }

      cairo_append_path (temp_cr, outline_path);
      cairo_translate (temp_cr, x, y);
      cairo_set_source (temp_cr, pattern);
      cairo_clip (temp_cr);
      cairo_paint (temp_cr);
      cairo_destroy (temp_cr);

      clipped_pattern = cairo_pattern_create_for_surface (clipped_surface);
      cairo_surface_destroy (clipped_surface);

      shadow_pattern = _st_create_shadow_cairo_pattern (shadow_spec,
                                                        clipped_pattern);
      cairo_pattern_destroy (clipped_pattern);
    }
  else
    {
      shadow_pattern = _st_create_shadow_cairo_pattern (shadow_spec,
                                                        pattern);
    }

  paint_shadow_pattern_to_cairo_context (shadow_spec,
                                         shadow_pattern, FALSE,
                                         cr,
                                         interior_path,
                                         outline_path);
  cairo_pattern_destroy (shadow_pattern);
}
