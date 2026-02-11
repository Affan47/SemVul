focusblur_brush_init_density (FblurBrush *brush)
{
  const gfloat   color_fnum = 1.0f / 255.0f;
  guint8        *dp = brush->data;
  gint           i = brush->length;
  float          sum = 0.0f;

  while (i --)
    sum += *dp ++;

  brush->original_density = sum * color_fnum;
}
