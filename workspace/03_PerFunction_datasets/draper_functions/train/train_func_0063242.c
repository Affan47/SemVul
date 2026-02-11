gegl_operation_context_get_object (GeglOperationContext *context,
                                   const gchar          *padname)
{
  GObject       *ret;
  GParamSpec    *pspec;
  GValue         value = { 0, };

  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (G_OBJECT (context->operation)), padname);
  g_value_init (&value, G_PARAM_SPEC_VALUE_TYPE (pspec));
  gegl_operation_context_get_property (context, padname, &value);

  ret = g_value_get_object (&value);

  if (!ret)
    {


    }
  g_value_unset (&value);
  return ret;
}
