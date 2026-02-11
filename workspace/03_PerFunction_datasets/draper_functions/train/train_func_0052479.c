gtk_clutter_actor_get_property (GObject    *gobject,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  GtkClutterActorPrivate *priv = GTK_CLUTTER_ACTOR (gobject)->priv;

  switch (prop_id)
    {
    case PROP_CONTENTS:
      g_value_set_object (value, gtk_bin_get_child (GTK_BIN (priv->widget)));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
    }
}
