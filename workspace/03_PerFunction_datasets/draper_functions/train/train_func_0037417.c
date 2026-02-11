gegl_operation_context_take_object (GeglOperationContext *context,
                                    const gchar          *padname,
                                    GObject              *data)
{
  GParamSpec *pspec;


  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (G_OBJECT (context->operation)), padname);

  if (pspec)
    {
      GValue value = {0, };
      g_value_init (&value, G_PARAM_SPEC_VALUE_TYPE (pspec));

      g_value_take_object (&value, data);
      gegl_operation_context_set_property (context, padname, &value);

      g_value_unset (&value);
    }
  else
    {
      g_warning ("%s: No paramspec found for pad '%s' on \"%s\"\n",
                 G_STRFUNC,
                 padname,
                 gegl_operation_get_name (context->operation));
    }
}
