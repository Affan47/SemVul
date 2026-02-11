gst_value_set_fraction (GValue * value, gint numerator, gint denominator)
{
  gint gcd = 0;

  g_return_if_fail (GST_VALUE_HOLDS_FRACTION (value));
  g_return_if_fail (denominator != 0);
  g_return_if_fail (denominator >= -G_MAXINT);
  g_return_if_fail (numerator >= -G_MAXINT);


  if (denominator < 0) {
    numerator = -numerator;
    denominator = -denominator;
  }


  gcd = gst_util_greatest_common_divisor (numerator, denominator);
  if (gcd) {
    numerator /= gcd;
    denominator /= gcd;
  }

  g_assert (denominator > 0);

  value->data[0].v_int = numerator;
  value->data[1].v_int = denominator;
}
