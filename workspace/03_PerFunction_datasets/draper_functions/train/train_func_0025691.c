operation_process (GeglOperation        *operation,
                                   GeglOperationContext *context,
                                   const gchar          *output_prop,
                                   const GeglRectangle  *result,
                                   gint                  level)
{
  GeglOperationClass  *operation_class;
  gpointer in, aux;
  operation_class = GEGL_OPERATION_CLASS (gegl_chant_parent_class);


  in = gegl_operation_context_get_object (context, "input");
  aux = gegl_operation_context_get_object (context, "aux");

  if (in && !aux && GEGL_CHANT_PROPERTIES (operation)->value == 1.0)
    {
      gegl_operation_context_take_object (context, "output",
                                          g_object_ref (G_OBJECT (in)));
      return TRUE;
    }


  return operation_class->process (operation, context, output_prop, result,
                                  gegl_operation_context_get_level (context));
}
