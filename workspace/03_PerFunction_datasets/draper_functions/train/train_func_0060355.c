gst_value_get_mini_object (const GValue * value)
{
  g_return_val_if_fail (GST_VALUE_HOLDS_MINI_OBJECT (value), NULL);

  return value->data[0].v_pointer;
}
