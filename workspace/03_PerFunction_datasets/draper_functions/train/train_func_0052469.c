gst_structure_set_name (GstStructure * structure, const gchar * name)
{
  g_return_if_fail (structure != NULL);
  g_return_if_fail (IS_MUTABLE (structure));
  g_return_if_fail (gst_structure_validate_name (name));

  structure->name = g_quark_from_string (name);
}
