compute_marshaller_name (MethodInfo *method, const char *prefix, GError **error)
{
  GString *ret;
  GArray *signature;
  GType rettype;
  const char *marshal_name;
  guint i;

  if (!compute_gsignature (method, &rettype, &signature, error))
    return NULL;

  ret = g_string_new (MARSHAL_PREFIX);
  g_string_append (ret, prefix);
  g_string_append_c (ret, '_');

  marshal_name = dbus_g_type_get_marshal_name (rettype);
  g_assert (marshal_name != NULL);
  g_string_append (ret, marshal_name);
  g_string_append (ret, "__");
  for (i = 0; i < signature->len; i++)
    {
      marshal_name = dbus_g_type_get_marshal_name (g_array_index (signature, GType, i));
      g_assert (marshal_name != NULL);
      g_string_append (ret, marshal_name);
      if (i < signature->len - 1)
	g_string_append_c (ret, '_');
    }
  if (signature->len == 0)
    {
      marshal_name = dbus_g_type_get_marshal_name (G_TYPE_NONE);
      g_assert (marshal_name != NULL);
      g_string_append (ret, marshal_name);
    }
  g_array_free (signature, TRUE);
  return g_string_free (ret, FALSE);
}
