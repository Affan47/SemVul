gst_structure_foreach (const GstStructure * structure,
    GstStructureForeachFunc func, gpointer user_data)
{
  guint i, len;
  GstStructureField *field;
  gboolean ret;

  g_return_val_if_fail (structure != NULL, FALSE);
  g_return_val_if_fail (func != NULL, FALSE);

  len = structure->fields->len;

  for (i = 0; i < len; i++) {
    field = GST_STRUCTURE_FIELD (structure, i);

    ret = func (field->name, &field->value, user_data);
    if (G_UNLIKELY (!ret))
      return FALSE;
  }

  return TRUE;
}
