gst_structure_nth_field_name (const GstStructure * structure, guint index)
{
  GstStructureField *field;

  g_return_val_if_fail (structure != NULL, NULL);
  g_return_val_if_fail (index < structure->fields->len, NULL);

  field = GST_STRUCTURE_FIELD (structure, index);

  return g_quark_to_string (field->name);
}
