ptrarray_iterator (GType                                   ptrarray_type,
		   gpointer                                instance,
		   DBusGTypeSpecializedCollectionIterator  iterator,
		   gpointer                                user_data)
{
  GPtrArray *ptrarray;
  GType elt_gtype;
  guint i;

  ptrarray = instance;

  elt_gtype = dbus_g_type_get_collection_specialization (ptrarray_type);

  for (i = 0; i < ptrarray->len; i++)
    {
      GValue val = {0, };
      g_value_init (&val, elt_gtype);
      gvalue_take_ptrarray_value (&val, g_ptr_array_index (ptrarray, i));
      iterator (&val, user_data);
    }
}
