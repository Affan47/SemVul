dbus_g_type_get_lookup_function (GType gtype)
{
  char *type_lookup;
  switch (gtype)
    {
      MAP_FUNDAMENTAL(CHAR);
      MAP_FUNDAMENTAL(UCHAR);
      MAP_FUNDAMENTAL(BOOLEAN);
      MAP_FUNDAMENTAL(LONG);
      MAP_FUNDAMENTAL(ULONG);
      MAP_FUNDAMENTAL(INT);
      MAP_FUNDAMENTAL(UINT);
      MAP_FUNDAMENTAL(INT64);
      MAP_FUNDAMENTAL(UINT64);
      MAP_FUNDAMENTAL(FLOAT);
      MAP_FUNDAMENTAL(DOUBLE);
      MAP_FUNDAMENTAL(STRING);
    }
  if (dbus_g_type_is_collection (gtype))
    {
      GType elt_gtype;
      char *sublookup;

      elt_gtype = dbus_g_type_get_collection_specialization (gtype);
      sublookup = dbus_g_type_get_lookup_function (elt_gtype);
      g_assert (sublookup);

      if (_dbus_g_type_is_fixed (elt_gtype))
        {
          type_lookup = g_strdup_printf ("dbus_g_type_get_collection "
              "(\"GArray\", %s)", sublookup);
        }
      else
        {
          type_lookup = g_strdup_printf ("dbus_g_type_get_collection "
              "(\"GPtrArray\", %s)", sublookup);
        }

      g_free (sublookup);

      return type_lookup;
    }
  else if (dbus_g_type_is_map (gtype))
    {
      GType key_gtype;
      char *key_lookup;
      GType value_gtype;
      char *value_lookup;

      key_gtype = dbus_g_type_get_map_key_specialization (gtype);
      value_gtype = dbus_g_type_get_map_value_specialization (gtype);
      key_lookup = dbus_g_type_get_lookup_function (key_gtype);
      g_assert (key_lookup);
      value_lookup = dbus_g_type_get_lookup_function (value_gtype);
      g_assert (value_lookup);
      type_lookup = g_strdup_printf ("dbus_g_type_get_map (\"GHashTable\", %s, %s)",
				     key_lookup, value_lookup);
      g_free (key_lookup);
      g_free (value_lookup);
      return type_lookup;
    }
  else if (dbus_g_type_is_struct (gtype))
    {
      GType value_gtype;
      GString *string;
      char *value_lookup = NULL;
      guint size, i;

      string = g_string_new ("dbus_g_type_get_struct (\"GValueArray\"");

      size = dbus_g_type_get_struct_size (gtype);
      for (i=0; i < size; i++)
        {
          value_gtype = dbus_g_type_get_struct_member_type(gtype, i);
          value_lookup = dbus_g_type_get_lookup_function (value_gtype);
          g_assert (value_lookup);
          g_string_append_printf (string, ", %s", value_lookup);
          g_free (value_lookup);
        }
      g_string_append (string, ", G_TYPE_INVALID)");
      return g_string_free (string, FALSE);
    }

  MAP_KNOWN(G_TYPE_VALUE);
  MAP_KNOWN(G_TYPE_STRV);
  MAP_KNOWN(G_TYPE_VALUE_ARRAY);
  MAP_KNOWN(DBUS_TYPE_G_PROXY);
  MAP_KNOWN(DBUS_TYPE_G_OBJECT_PATH);
  MAP_KNOWN(DBUS_TYPE_G_SIGNATURE);
  return NULL;
}
