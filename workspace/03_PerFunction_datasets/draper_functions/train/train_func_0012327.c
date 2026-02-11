glade_widget_adaptor_get_property (GladeWidgetAdaptor *adaptor,
                                   GObject *object,
                                   const gchar *property_name,
                                   GValue *value)
{
  g_return_if_fail (GLADE_IS_WIDGET_ADAPTOR (adaptor));
  g_return_if_fail (G_IS_OBJECT (object));
  g_return_if_fail (property_name != NULL && value != NULL);
  g_return_if_fail (g_type_is_a (G_OBJECT_TYPE (object), adaptor->priv->type));


  GLADE_WIDGET_ADAPTOR_GET_CLASS
      (adaptor)->get_property (adaptor, object, property_name, value);
}
