gegl_render_op (GeglBuffer *source_buffer,
                GeglBuffer *target_buffer,
                const gchar *first_property_name,
                ...)
{
  va_list var_args;

  g_return_if_fail (GEGL_IS_BUFFER (source_buffer));
  g_return_if_fail (GEGL_IS_BUFFER (target_buffer));

  va_start (var_args, first_property_name);
  gegl_render_op_valist (source_buffer, target_buffer,
                         first_property_name, var_args);
  va_end (var_args);
}
