find_param_spec_in_interfaces (GPtrArray   *type_structs,
                               const gchar *name)
{
  guint i;

  for (i = 0; i < type_structs->len; ++i)
    {
      GParamSpec *pspec;

      pspec = g_object_interface_find_property (g_ptr_array_index (type_structs, i),
                                                name);

      if (pspec != NULL)
        return pspec;
    }

  return NULL;
}
