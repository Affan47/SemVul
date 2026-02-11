tp_properties_mixin_get_properties (GObject *obj,
                                    const GArray *properties,
                                    GPtrArray **ret,
                                    GError **error)
{
  TpPropertiesMixin *mixin = TP_PROPERTIES_MIXIN (obj);
  TpPropertiesMixinClass *mixin_cls = TP_PROPERTIES_MIXIN_CLASS (
                                            G_OBJECT_GET_CLASS (obj));
  GType value_type = TP_STRUCT_TYPE_PROPERTY_VALUE;
  guint i;


  for (i = 0; i < properties->len; i++)
    {
      guint prop_id = g_array_index (properties, guint, i);


      if (prop_id >= mixin_cls->num_props)
        {
          g_set_error (error, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
              "invalid property identifier %d", prop_id);

          return FALSE;
        }


      if (!tp_properties_mixin_is_readable (obj, prop_id))
        {
          g_set_error (error, TP_ERROR, TP_ERROR_PERMISSION_DENIED,
              "permission denied for property identifier %d", prop_id);

          return FALSE;
        }
    }


  *ret = g_ptr_array_sized_new (properties->len);

  for (i = 0; i < properties->len; i++)
    {
      guint prop_id = g_array_index (properties, guint, i);
      GValue val_struct = { 0, };


      g_value_init (&val_struct, value_type);
      g_value_take_boxed (&val_struct,
          dbus_g_type_specialized_construct (value_type));

      dbus_g_type_struct_set (&val_struct,
          0, prop_id,
          1, mixin->properties[prop_id].value,
          G_MAXUINT);

      g_ptr_array_add (*ret, g_value_get_boxed (&val_struct));
    }

  return TRUE;
}
