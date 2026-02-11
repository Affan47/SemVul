gst_caps_set_simple_valist (GstCaps * caps, const char *field, va_list varargs)
{
  GValue value = { 0, };

  g_return_if_fail (GST_IS_CAPS (caps));
  g_return_if_fail (IS_WRITABLE (caps));

  while (field) {
    GType type;
    char *err;

    type = va_arg (varargs, GType);

    if (G_UNLIKELY (type == G_TYPE_DATE)) {
      g_warning ("Don't use G_TYPE_DATE, use GST_TYPE_DATE instead\n");
      type = GST_TYPE_DATE;
    }
    G_VALUE_COLLECT_INIT (&value, type, varargs, 0, &err);
    if (G_UNLIKELY (err)) {
      g_critical ("%s", err);
      return;
    }

    gst_caps_set_value (caps, field, &value);

    g_value_unset (&value);

    field = va_arg (varargs, const gchar *);
  }
}
