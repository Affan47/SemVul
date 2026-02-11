gegl_sampler_get_from_buffer (GeglSampler *const sampler,
                              const gint         x,
                              const gint         y)
{
  guchar *buffer_ptr;
  gint    dx;
  gint    dy;
  gint    sof;

  const gint bpp =
    babl_format_get_bytes_per_pixel (sampler->interpolate_format);


  const gint maximum_width_and_height = 64;
  g_assert (sampler->context_rect[0].width  <= maximum_width_and_height);
  g_assert (sampler->context_rect[0].height <= maximum_width_and_height);

  if (( sampler->sampler_buffer[0] == NULL )
      ||
      ( x < sampler->sampler_rectangle[0].x )
      ||
      ( y < sampler->sampler_rectangle[0].y )
      ||
      ( x >= sampler->sampler_rectangle[0].x + sampler->sampler_rectangle[0].width )
      ||
      ( y >= sampler->sampler_rectangle[0].y + sampler->sampler_rectangle[0].height ))
    {


      GeglRectangle fetch_rectangle;

      fetch_rectangle.x =
        x - ( maximum_width_and_height - sampler->context_rect[0].width  ) / 8;
      fetch_rectangle.y =
        y - ( maximum_width_and_height - sampler->context_rect[0].height ) / 8;

      fetch_rectangle.width  = maximum_width_and_height;
      fetch_rectangle.height = maximum_width_and_height;

      if (sampler->sampler_buffer[0] == NULL)
        {


          sampler->sampler_buffer[0] =
            g_malloc0 (( maximum_width_and_height * maximum_width_and_height )
                       * bpp);
        }

      gegl_buffer_get (sampler->buffer,
                       &fetch_rectangle,
                       1.0,
                       sampler->interpolate_format,
                       sampler->sampler_buffer[0],
                       GEGL_AUTO_ROWSTRIDE,
                       GEGL_ABYSS_NONE);

      sampler->sampler_rectangle[0] = fetch_rectangle;
    }

  dx = x - sampler->sampler_rectangle[0].x;
  dy = y - sampler->sampler_rectangle[0].y;
  buffer_ptr = (guchar *)sampler->sampler_buffer[0];
  sof = ( dx + dy * sampler->sampler_rectangle[0].width ) * bpp;

  return (gfloat*)(buffer_ptr+sof);
}
