tp_base_contact_list_mixin_class_init (TpBaseConnectionClass *cls)
{
  GType type = G_OBJECT_CLASS_TYPE (cls);
  GObjectClass *obj_cls = (GObjectClass *) cls;

  g_return_if_fail (TP_IS_BASE_CONNECTION_CLASS (cls));
  g_return_if_fail (TP_CONTACTS_MIXIN_CLASS (cls) != NULL);
  g_return_if_fail (g_type_is_a (type,
        TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_LIST));

  tp_dbus_properties_mixin_implement_interface (obj_cls,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_LIST,
      tp_base_contact_list_get_list_dbus_property,
      NULL, known_list_props);

  if (g_type_is_a (type, TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_GROUPS))
    {
      tp_dbus_properties_mixin_implement_interface (obj_cls,
          TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_GROUPS,
          tp_base_contact_list_get_group_dbus_property,
          NULL, known_group_props);
    }

  if (g_type_is_a (type, TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_BLOCKING))
    {
      tp_dbus_properties_mixin_implement_interface (obj_cls,
          TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_BLOCKING,
          tp_base_contact_list_get_blocking_dbus_property,
          NULL, known_blocking_props);
    }
}
