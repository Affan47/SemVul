gst_structure_can_intersect (const GstStructure * struct1,
    const GstStructure * struct2)
{
  g_return_val_if_fail (GST_IS_STRUCTURE (struct1), FALSE);
  g_return_val_if_fail (GST_IS_STRUCTURE (struct2), FALSE);

  if (G_UNLIKELY (struct1->name != struct2->name))
    return FALSE;


  return gst_structure_foreach ((GstStructure *) struct1,
      gst_caps_structure_can_intersect_field, (gpointer) struct2);
}
