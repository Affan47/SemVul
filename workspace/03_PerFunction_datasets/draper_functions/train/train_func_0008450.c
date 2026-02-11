glade_base_editor_get_property (GObject * object,
                                guint prop_id,
                                GValue * value, GParamSpec * pspec)
{
  GladeBaseEditor *editor = GLADE_BASE_EDITOR (object);

  switch (prop_id)
    {
      case PROP_CONTAINER:
        g_value_set_object (value, glade_widget_get_object (editor->priv->gcontainer));
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
