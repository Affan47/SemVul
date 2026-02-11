glade_widget_adaptor_get_children (GladeWidgetAdaptor *adaptor,
                                   GObject *container)
{
  g_return_val_if_fail (GLADE_IS_WIDGET_ADAPTOR (adaptor), NULL);
  g_return_val_if_fail (G_IS_OBJECT (container), NULL);
  g_return_val_if_fail (g_type_is_a (G_OBJECT_TYPE (container), adaptor->priv->type),
                        NULL);

  return GLADE_WIDGET_ADAPTOR_GET_CLASS (adaptor)->get_children (adaptor, container);
}
