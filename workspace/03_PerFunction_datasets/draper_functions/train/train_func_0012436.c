process (GeglOperation        *op,
          void                *in_buf,
          void                *aux_buf,
          void                *out_buf,
          glong                n_pixels,
          const GeglRectangle *roi,
          gint                 level)
{
  gint i;
  gfloat * GEGL_ALIGNED in = in_buf;
  gfloat * GEGL_ALIGNED aux = aux_buf;
  gfloat * GEGL_ALIGNED out = out_buf;

  if (aux==NULL)
    return TRUE;

  for (i = 0; i < n_pixels; i++)
    {
      gint   j;
      gfloat aA G_GNUC_UNUSED, aB G_GNUC_UNUSED, aD G_GNUC_UNUSED;

      aB = in[3];
      aA = aux[3];
      aD = aB;

      for (j = 0; j < 3; j++)
        {
          gfloat cA G_GNUC_UNUSED, cB G_GNUC_UNUSED;

          cB = in[j];
          cA = aux[j];
          out[j] = cA * aB + cB * (1.0f - aA);
        }
      out[3] = aD;
      in  += 4;
      aux += 4;
      out += 4;
    }
  return TRUE;
}
