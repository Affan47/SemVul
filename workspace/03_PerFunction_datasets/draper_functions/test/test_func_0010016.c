mx_stylable_get (MxStylable  *stylable,
                 const gchar *first_property_name,
                 ...)
{
  MxStyle *style;
  va_list args;

  g_return_if_fail (MX_IS_STYLABLE (stylable));
  g_return_if_fail (first_property_name != NULL);

  style = mx_stylable_get_style (stylable);

  va_start (args, first_property_name);
  mx_style_get_valist (style, stylable, first_property_name, args);
  va_end (args);
}
