gegl_operation_context_set_object (GeglOperationContext *context,
                                   const gchar          *padname,
                                   GObject              *data)
{

  if (data)
    g_object_ref (data);
  gegl_operation_context_take_object (context, padname, data);
}
