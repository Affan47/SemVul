gegl_operation_list_properties (const gchar *operation_type,
                                guint       *n_properties_p)
{
  GParamSpec  **pspecs;
  GType         type;
  GObjectClass *klass;

  type = gegl_operation_gtype_from_name (operation_type);
  if (!type)
    {
      if (n_properties_p)
        *n_properties_p = 0;
      return NULL;
    }
  klass  = g_type_class_ref (type);
  pspecs = g_object_class_list_properties (klass, n_properties_p);
  g_type_class_unref (klass);
  return pspecs;
}
