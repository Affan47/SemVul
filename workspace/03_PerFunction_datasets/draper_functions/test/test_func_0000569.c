proxy_lcopy_value (const GValue *value,
		   guint         n_collect_values,
		   GTypeCValue  *collect_values,
		   guint         collect_flags)
{
  gpointer *boxed_p = collect_values[0].v_pointer;

  if (!boxed_p)
    return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));

  if (!value->data[0].v_pointer)
    *boxed_p = NULL;
  else if (collect_flags & G_VALUE_NOCOPY_CONTENTS)
    *boxed_p = value->data[0].v_pointer;
  else
    {
      DBusGTypeSpecializedData *data;
      GType type;

      type = G_VALUE_TYPE (value);
      data = lookup_specialization_data (type);

      *boxed_p = data->klass->vtable->copy_func (type, value->data[0].v_pointer);
    }

  return NULL;
}
