gst_element_class_install_std_props (GstElementClass * klass,
    const gchar * first_name, ...)
{
  const char *name;

  va_list args;

  g_return_if_fail (GST_IS_ELEMENT_CLASS (klass));

  va_start (args, first_name);

  name = first_name;

  while (name) {
    int arg_id = va_arg (args, int);
    GParamFlags flags = (GParamFlags) va_arg (args, int);

    gst_element_populate_std_props ((GObjectClass *) klass, name, arg_id,
        flags);

    name = va_arg (args, char *);
  }

  va_end (args);
}
