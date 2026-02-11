gst_color_balance_get_balance_type (GstColorBalance * balance)
{
  GstColorBalanceClass *klass;

  g_return_val_if_fail (GST_IS_COLOR_BALANCE (balance),
      GST_COLOR_BALANCE_SOFTWARE);

  klass = GST_COLOR_BALANCE_GET_CLASS (balance);

  return klass->balance_type;
}
