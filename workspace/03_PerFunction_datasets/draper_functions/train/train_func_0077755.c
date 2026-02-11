gst_value_intersect_fraction_fraction_range (GValue * dest, const GValue * src1,
    const GValue * src2)
{
  gint res1, res2;
  GValue *vals;
  GstValueCompareFunc compare;

  vals = src2->data[0].v_pointer;

  if (vals == NULL)
    return FALSE;

  if ((compare = gst_value_get_compare_func (src1))) {
    res1 = gst_value_compare_with_func (&vals[0], src1, compare);
    res2 = gst_value_compare_with_func (&vals[1], src1, compare);

    if ((res1 == GST_VALUE_EQUAL || res1 == GST_VALUE_LESS_THAN) &&
        (res2 == GST_VALUE_EQUAL || res2 == GST_VALUE_GREATER_THAN)) {
      if (dest)
        gst_value_init_and_copy (dest, src1);
      return TRUE;
    }
  }

  return FALSE;
}
