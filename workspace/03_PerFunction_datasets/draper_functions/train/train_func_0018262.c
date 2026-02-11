gst_value_fraction_multiply (GValue * product, const GValue * factor1,
    const GValue * factor2)
{
  gint n1, n2, d1, d2;
  gint res_n, res_d;

  g_return_val_if_fail (product != NULL, FALSE);
  g_return_val_if_fail (GST_VALUE_HOLDS_FRACTION (factor1), FALSE);
  g_return_val_if_fail (GST_VALUE_HOLDS_FRACTION (factor2), FALSE);

  n1 = factor1->data[0].v_int;
  n2 = factor2->data[0].v_int;
  d1 = factor1->data[1].v_int;
  d2 = factor2->data[1].v_int;

  if (!gst_util_fraction_multiply (n1, d1, n2, d2, &res_n, &res_d))
    return FALSE;

  gst_value_set_fraction (product, res_n, res_d);

  return TRUE;
}
