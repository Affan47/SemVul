glade_widget_drag_can_drop (_GladeDrag *dest, gint x, gint y, GObject *data)
{
  GObject *object;

  g_return_val_if_fail (GLADE_IS_DRAG (dest), FALSE);

  object = GLADE_WIDGET (dest)->priv->object;

  if (!(GTK_IS_FIXED (object) ||
        GTK_IS_LAYOUT (object) ||
        GTK_IS_OVERLAY (object)))
    return FALSE;

  if (GLADE_IS_WIDGET_ADAPTOR (data))
    {
      GType otype = glade_widget_adaptor_get_object_type (GLADE_WIDGET_ADAPTOR (data));

      if (g_type_is_a (otype, GTK_TYPE_WIDGET) && !GWA_IS_TOPLEVEL (data))
        return TRUE;
    }
  else
    {
      GladeWidget *new_child, *parent = GLADE_WIDGET (dest);
      GObject *object = glade_widget_get_object (parent);

      if (object == data)
        return FALSE;

      if (GTK_IS_WIDGET (data) && GTK_IS_WIDGET (object) &&
          gtk_widget_is_ancestor (GTK_WIDGET (data), GTK_WIDGET (object)))
        return FALSE;

      if ((new_child = glade_widget_get_from_gobject (data)) &&
          (!glade_widget_add_verify (parent, new_child, FALSE) ||
           glade_widget_placeholder_relation (parent, new_child)))
        return FALSE;

      return TRUE;
    }

  return FALSE;
}
