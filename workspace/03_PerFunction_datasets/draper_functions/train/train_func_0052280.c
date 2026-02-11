focusblur_brush_update_balance (FblurBrush      *brush,
                                gboolean         balance)
{
  gfloat tmp_x, tmp_y;

  g_return_val_if_fail (brush != NULL, TRUE);

  if (brush->balance == balance)
    return FALSE;

  tmp_x = brush->center_x;
  tmp_y = brush->center_y;

  focusblur_brush_init_balance (brush, balance);

  if (brush->center_x == tmp_x &&
      brush->center_y == tmp_y)
    return FALSE;

  focusblur_brush_init_radius (brush);

  return TRUE;
}
