get_services (SwCoreIface *self, DBusGMethodInvocation *context)
{
  SwCore *core = SW_CORE (self);
  SwCorePrivate *priv = core->priv;
  GPtrArray *array;
  GList *l;

  array = g_ptr_array_new ();

  l = g_hash_table_get_keys (priv->service_types);
  while (l) {
    g_ptr_array_add (array, l->data);
    l = g_list_delete_link (l, l);
  }
  g_ptr_array_add (array, NULL);

  sw_core_iface_return_from_get_services (context, (const gpointer)array->pdata);

  g_ptr_array_free (array, TRUE);
}
