glade_property_equals_va_list (GladeProperty * property, va_list vl)
{
  GValue *value;
  gboolean ret;

  g_return_val_if_fail (GLADE_IS_PROPERTY (property), FALSE);

  value = glade_property_class_make_gvalue_from_vl (property->priv->klass, vl);

  ret = GLADE_PROPERTY_GET_KLASS (property)->equals_value (property, value);

  g_value_unset (value);
  g_free (value);
  return ret;
}
