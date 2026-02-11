proxy_value_free (GValue *value)
{
  if (value->data[0].v_pointer && !(value->data[1].v_uint & G_VALUE_NOCOPY_CONTENTS))
    {
      DBusGTypeSpecializedData *data;
      GType type;

      type = G_VALUE_TYPE (value);
      data = lookup_specialization_data (type);
      g_assert (data != NULL);

      if (data->klass->vtable->free_func)
        {
          data->klass->vtable->free_func (type, value->data[0].v_pointer);
        }
      else
        {
          g_assert (data->klass->vtable->simple_free_func != NULL);
          data->klass->vtable->simple_free_func (value->data[0].v_pointer);
        }
    }
}
