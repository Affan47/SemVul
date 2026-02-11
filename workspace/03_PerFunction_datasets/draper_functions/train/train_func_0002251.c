priv_gst_structure_append_to_gstring (const GstStructure * structure,
    GString * s)
{
  GstStructureField *field;
  guint i, len;

  g_return_val_if_fail (s != NULL, FALSE);

  g_string_append (s, g_quark_to_string (structure->name));
  len = structure->fields->len;
  for (i = 0; i < len; i++) {
    char *t;
    GType type;

    field = GST_STRUCTURE_FIELD (structure, i);

    t = gst_value_serialize (&field->value);
    type = gst_structure_value_get_generic_type (&field->value);

    g_string_append_len (s, ", ", 2);

    g_string_append (s, g_quark_to_string (field->name));
    g_string_append_len (s, "=(", 2);
    g_string_append (s, gst_structure_to_abbr (type));
    g_string_append_c (s, ')');
    g_string_append (s, t == NULL ? "NULL" : t);
    g_free (t);
  }

  g_string_append_c (s, ';');
  return TRUE;
}
