gst_structure_remove_all_fields (GstStructure * structure)
{
  GstStructureField *field;
  int i;

  g_return_if_fail (structure != NULL);
  g_return_if_fail (IS_MUTABLE (structure));

  for (i = GST_STRUCTURE_FIELDS (structure)->len - 1; i >= 0; i--) {
    field = GST_STRUCTURE_FIELD (structure, i);

    if (G_IS_VALUE (&field->value)) {
      g_value_unset (&field->value);
    }
    GST_STRUCTURE_FIELDS (structure) =
        g_array_remove_index (GST_STRUCTURE_FIELDS (structure), i);
  }
}
