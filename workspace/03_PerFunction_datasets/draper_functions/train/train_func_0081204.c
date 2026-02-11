gst_structure_copy (const GstStructure * structure)
{
  GstStructure *new_structure;
  GstStructureField *field;
  guint i, len;

  g_return_val_if_fail (structure != NULL, NULL);

  len = structure->fields->len;
  new_structure = gst_structure_id_empty_new_with_size (structure->name, len);

  for (i = 0; i < len; i++) {
    GstStructureField new_field = { 0 };

    field = GST_STRUCTURE_FIELD (structure, i);

    new_field.name = field->name;
    gst_value_init_and_copy (&new_field.value, &field->value);
    g_array_append_val (new_structure->fields, new_field);
  }

  return new_structure;
}
