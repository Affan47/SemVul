paint_shadow_pattern_to_cairo_context (StShadow *shadow_spec,
                                       cairo_pattern_t *pattern,
                                       gboolean         fill_exterior,
                                       cairo_t         *cr,
                                       cairo_path_t    *interior_path,
                                       cairo_path_t    *outline_path)
{


  cairo_path_t *path = (interior_path != NULL) ? interior_path : outline_path;
  double x1, x2, y1, y2;


  g_assert (!(fill_exterior && path == NULL));

  cairo_save (cr);
  if (path != NULL)
    {
      cairo_append_path (cr, path);


      if (fill_exterior)
        {
          cairo_path_extents (cr, &x1, &y1, &x2, &y2);
          x1 = floor (x1);
          y1 = floor (y1);
          x2 = ceil (x2);
          y2 = ceil (y2);
        }

      cairo_clip (cr);
    }

  cairo_set_source_rgba (cr,
                         shadow_spec->color.red / 255.0,
                         shadow_spec->color.green / 255.0,
                         shadow_spec->color.blue / 255.0,
                         shadow_spec->color.alpha / 255.0);
  if (fill_exterior)
    {
      cairo_surface_t *surface;
      int width, height;
      cairo_matrix_t matrix;

      cairo_save (cr);


      cairo_rectangle (cr, x1, y1, x2 - x1, y2 - y1);


      cairo_pattern_get_surface (pattern, &surface);
      width = cairo_image_surface_get_width  (surface);
      height = cairo_image_surface_get_height (surface);

      cairo_pattern_get_matrix (pattern, &matrix);
      cairo_matrix_invert (&matrix);
      cairo_transform (cr, &matrix);

      cairo_rectangle (cr, 0, height, width, - height);
      cairo_fill (cr);

      cairo_restore (cr);
    }

  cairo_mask (cr, pattern);
  cairo_restore (cr);
}
