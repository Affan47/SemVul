gst_structure_is_equal (const GstStructure * structure1,
    const GstStructure * structure2)
{
  g_return_val_if_fail (GST_IS_STRUCTURE (structure1), FALSE);
  g_return_val_if_fail (GST_IS_STRUCTURE (structure2), FALSE);

  if (G_UNLIKELY (structure1 == structure2))
    return TRUE;

  if (structure1->name != structure2->name) {
    return FALSE;
  }
  if (GST_STRUCTURE_FIELDS (structure1)->len !=
      GST_STRUCTURE_FIELDS (structure2)->len) {
    return FALSE;
  }

  return gst_structure_foreach (structure1, gst_structure_is_equal_foreach,
      (gpointer) structure2);
}
