egg_wrap_box_set_child_property (GtkContainer    *container,
                                 GtkWidget       *widget,
                                 guint            property_id,
                                 const GValue    *value,
                                 GParamSpec      *pspec)
{
  EggWrapBox        *box  = EGG_WRAP_BOX (container);
  EggWrapBoxPrivate *priv = box->priv;
  EggWrapBoxChild   *child;
  GList             *list;

  list = g_list_find_custom (priv->children, widget,
                             (GCompareFunc)find_child_in_list);
  g_return_if_fail (list != NULL);

  child = list->data;

  switch (property_id)
    {
    case CHILD_PROP_PACKING:
      child->packing = g_value_get_flags (value);
      break;
    default:
      GTK_CONTAINER_WARN_INVALID_CHILD_PROPERTY_ID (container, property_id, pspec);
      break;
    }

  if (gtk_widget_get_visible (widget) &&
      gtk_widget_get_visible (GTK_WIDGET (box)))
    gtk_widget_queue_resize (widget);
}
