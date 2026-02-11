sw_contact_view_constructed (GObject *object)
{
  SwContactView *contact_view = SW_CONTACT_VIEW (object);
  SwContactViewPrivate *priv = GET_PRIVATE (contact_view);
  SwCore *core;

  core = sw_core_dup_singleton ();

  priv->object_path = _make_object_path (contact_view);
  dbus_g_connection_register_g_object (sw_core_get_connection (core),
                                       priv->object_path,
                                       G_OBJECT (contact_view));
  g_object_unref (core);


  if (G_OBJECT_CLASS (sw_contact_view_parent_class)->constructed)
    G_OBJECT_CLASS (sw_contact_view_parent_class)->constructed (object);
}
