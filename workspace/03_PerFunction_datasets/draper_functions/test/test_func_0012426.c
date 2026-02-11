_gst_param_fraction_validate (GParamSpec * pspec, GValue * value)
{
  GstParamSpecFraction *fspec = GST_PARAM_SPEC_FRACTION (pspec);
  gboolean within_range = FALSE;
  GValue f_this = { 0, };
  GValue f_min = { 0, };
  GValue f_max = { 0, };
  gint res;

  g_value_init (&f_this, GST_TYPE_FRACTION);
  gst_value_set_fraction (&f_this, value->data[0].v_int, value->data[1].v_int);

  g_value_init (&f_min, GST_TYPE_FRACTION);
  gst_value_set_fraction (&f_min, fspec->min_num, fspec->min_den);

  g_value_init (&f_max, GST_TYPE_FRACTION);
  gst_value_set_fraction (&f_max, fspec->max_num, fspec->max_den);

  res = gst_value_compare (&f_min, &f_this);
#ifndef GST_DISABLE_GST_DEBUG
  GST_LOG ("comparing %d/%d to %d/%d, result = %d", fspec->min_num,
      fspec->min_den, value->data[0].v_int, value->data[1].v_int, res);
#endif
  if (res != GST_VALUE_LESS_THAN && res != GST_VALUE_EQUAL)
    goto out;

#ifndef GST_DISABLE_GST_DEBUG
  GST_LOG ("comparing %d/%d to %d/%d, result = %d", value->data[0].v_int,
      value->data[1].v_int, fspec->max_num, fspec->max_den, res);
#endif
  res = gst_value_compare (&f_this, &f_max);
  if (res != GST_VALUE_LESS_THAN && res != GST_VALUE_EQUAL)
    goto out;

  within_range = TRUE;

out:

  g_value_unset (&f_min);
  g_value_unset (&f_max);
  g_value_unset (&f_this);

#ifndef GST_DISABLE_GST_DEBUG
  GST_LOG ("%swithin range", (within_range) ? "" : "not ");
#endif


  return !within_range;
}
