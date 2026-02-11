focusblur_brush_init_balance (FblurBrush *brush,
                              gboolean    balance)
{
  const gfloat   color_fnum = 1.0f / 255.0f;
  guint8        *dp, *dlp;
  gint           x, y;
  gfloat         sum, sumb, half;

  brush->balance = balance;

  if (! balance)
    {
      brush->center_x = (gfloat) (brush->width  - 1) / 2.0f;
      brush->center_y = (gfloat) (brush->height - 1) / 2.0f;

      return;
    }


  half = brush->original_density / color_fnum / 2.0f;


  sum = sumb = 0.0f;
  for (y = 0, dp = brush->data; y < brush->height; y ++)
    for (x = 0; x < brush->width; x ++, dp ++)
      {
        sum += *dp;
        if (sum >= half)
          {
            brush->center_y = y + (half - sumb) / (sum - sumb) - 0.5f;
            goto break_y;
          }
        sumb = sum;
      }
 break_y:


  sum = sumb = 0.0f;
  for (x = 0, dlp = brush->data; x < brush->width; x ++, dlp ++)
    for (y = 0, dp = dlp; y < brush->height; y ++, dp += brush->width)
      {
        sum += *dp;
        if (sum >= half)
          {
            brush->center_x = x + (half - sumb) / (sum - sumb) - 0.5f;
            goto break_x;
          }
        sumb = sum;
      }
 break_x:

  return;
}
