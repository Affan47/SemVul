evd_connection_pool_new (const gchar *address, GType connection_type)
{
  EvdConnectionPool *self;

  g_return_val_if_fail (address != NULL, NULL);
  g_return_val_if_fail (g_type_is_a (connection_type, EVD_TYPE_CONNECTION),
                        NULL);

  self = g_object_new (EVD_TYPE_CONNECTION_POOL,
                       "address", address,
                       "connection-type", connection_type,
                       NULL);

  return self;
}
