gst_structure_get_boolean (const GstStructure * structure,
    const gchar * fieldname, gboolean * value)
{
  GstStructureField *field;

  g_return_val_if_fail (structure != NULL, FALSE);
  g_return_val_if_fail (fieldname != NULL, FALSE);

  field = gst_structure_get_field (structure, fieldname);

  if (field == NULL)
    return FALSE;
  if (!G_VALUE_HOLDS_BOOLEAN (&field->value))
    return FALSE;

  *value = gst_g_value_get_boolean_unchecked (&field->value);

  return TRUE;
}
