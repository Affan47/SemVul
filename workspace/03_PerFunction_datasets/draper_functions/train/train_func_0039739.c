gst_value_set_structure (GValue * value, const GstStructure * structure)
{
  g_return_if_fail (G_IS_VALUE (value));
  g_return_if_fail (G_VALUE_TYPE (value) == GST_TYPE_STRUCTURE);
  g_return_if_fail (structure == NULL || GST_IS_STRUCTURE (structure));

  g_value_set_boxed (value, structure);
}
