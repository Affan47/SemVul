focusblur_brush_new (gchar      *brush_name,
                     gboolean    balance)
{
  FblurBrush    *brush;
  gboolean       ret;
  gint           width, height;
  gint           mask_bpp, num_mask_bytes;
  gint           color_bpp, num_color_bytes;
  guint8        *mask_bytes, *color_bytes;

  ret = gimp_brush_get_pixels (brush_name, &width, &height,
                               &mask_bpp,  &num_mask_bytes,  &mask_bytes,
                               &color_bpp, &num_color_bytes, &color_bytes);
  if (! ret)
    {
      gimp_message (_("gimp_brush_get_pixels() is failed."));
      g_free (mask_bytes);
      return NULL;
    }

  g_assert (mask_bpp == 1);


  if (color_bytes)
    {
      gfloat             tval = 1.0f / 255.0f / color_bpp;
      guint8            *mp = mask_bytes;
      guint8            *cp = color_bytes;
      gint               i, b, cval;

      for (i = num_mask_bytes; i --; mp ++, cp += color_bpp)
        if (*mp)
          {
            cval = 0;
            for (b = 0; b < color_bpp; b ++)
              cval += cp[b];
            *mp = rint (cval * *mp * tval);
          }

      g_free (color_bytes);
    }

  brush                 = g_new0 (FblurBrush, 1);
  brush->cache_rotate   = -1;
  brush->name           = g_strdup (brush_name);
  brush->width          = width;
  brush->height         = height;
  brush->length         = num_mask_bytes;
  brush->data           = mask_bytes;

  focusblur_brush_init_density (brush);

  if (brush->original_density <= 0.0f)
    {
      focusblur_brush_destroy (&brush);
      return NULL;
    }

  focusblur_brush_init_balance (brush, balance);
  focusblur_brush_init_radius (brush);

  return brush;
}
