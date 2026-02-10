process (GeglOperation       *operation,
         GeglBuffer          *input,
         GeglBuffer          *output,
         const GeglRectangle *result,
         gint                 level)
{
  GeglChantO *o                    = GEGL_CHANT_PROPERTIES (operation);

  gint x = result->x;
  gint y = result->y;

  gfloat *dst_buf = g_slice_alloc (result->width * result->height * 4 * sizeof(gfloat));

  gfloat *out_pixel = dst_buf;

  GeglSampler *sampler = gegl_buffer_sampler_new (input,
                                                  babl_format ("RGBA float"),
                                                  o->sampler_type);

  gint n_pixels = result->width * result->height;

  while (n_pixels--)
    {
      gdouble shift;
      gdouble coordsx;
      gdouble coordsy;
      gdouble lambda;

      gdouble angle_rad = o->angle / 180.0 * G_PI;
      gdouble nx = x * cos (angle_rad) + y * sin (angle_rad);

      switch (o->wave_type)
        {
          case GEGl_RIPPLE_WAVE_TYPE_SAWTOOTH:
            lambda = div (nx,o->period).rem - o->phi * o->period;
            if (lambda < 0)
              lambda += o->period;
            shift = o->amplitude * (fabs (((lambda / o->period) * 4) - 2) - 1);
            break;
          case GEGl_RIPPLE_WAVE_TYPE_SINE:
          default:
            shift = o->amplitude * sin (2.0 * G_PI * nx / o->period + 2.0 * G_PI * o->phi);
            break;
        }

      coordsx = x + shift * sin (angle_rad);
      coordsy = y + shift * cos (angle_rad);

      gegl_sampler_get (sampler,
                        coordsx,
                        coordsy,
                        NULL,
                        out_pixel);

      out_pixel += 4;


      x++;
      if (x>=result->x + result->width)
        {
          x=result->x;
          y++;
        }
    }

  gegl_buffer_set (output, result, 0, babl_format ("RGBA float"), dst_buf, GEGL_AUTO_ROWSTRIDE);
  g_slice_free1 (result->width * result->height * 4 * sizeof(gfloat), dst_buf);

  g_object_unref (sampler);

  return  TRUE;
}
