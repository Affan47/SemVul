fv_text_handle_set_property (GObject      *object,
                             guint         prop_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
  FvTextHandlePrivate *priv;
  FvTextHandle *handle;

  handle = FV_TEXT_HANDLE (object);
  priv = handle->priv;

  switch (prop_id)
    {
    case PROP_PARENT:
      priv->parent = GTK_WIDGET(g_value_dup_object (value));
      break;
    case PROP_RELATIVE_TO:
      _fv_text_handle_set_relative_to (handle,
                                       GDK_WINDOW(g_value_get_object (value)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}
