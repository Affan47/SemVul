gst_value_compare_fraction (const GValue * value1, const GValue * value2)
{
  gint n1, n2;
  gint d1, d2;
  gint ret;

  n1 = value1->data[0].v_int;
  n2 = value2->data[0].v_int;
  d1 = value1->data[1].v_int;
  d2 = value2->data[1].v_int;


  if (n1 == n2 && d1 == d2)
    return GST_VALUE_EQUAL;

  if (d1 == 0 && d2 == 0)
    return GST_VALUE_UNORDERED;
  else if (d1 == 0)
    return GST_VALUE_GREATER_THAN;
  else if (d2 == 0)
    return GST_VALUE_LESS_THAN;

  ret = gst_util_fraction_compare (n1, d1, n2, d2);
  if (ret == -1)
    return GST_VALUE_LESS_THAN;
  else if (ret == 1)
    return GST_VALUE_GREATER_THAN;


  g_return_val_if_reached (GST_VALUE_UNORDERED);
}
