process (GeglOperation        *operation,
         GeglOperationContext *context,
         const gchar          *output_prop,
         const GeglRectangle  *result,
         gint                  level)
{
  GeglBuffer *input;

  if (strcmp (output_prop, "output"))
    {
      g_warning ("requested processing of %s pad on a clone", output_prop);
      return FALSE;
    }

  input  = gegl_operation_context_get_source (context, "input");
  if (!input)
    {
      g_warning ("clone received NULL input");
      return FALSE;
    }

  gegl_operation_context_take_object (context, "output", G_OBJECT (input));
  return TRUE;
}
