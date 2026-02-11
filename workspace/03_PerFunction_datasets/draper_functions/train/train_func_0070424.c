evd_dbus_agent_bind_connection_to_object (ObjectData  *obj_data,
                                          ObjConnData *obj_conn_data)
{
  guint *conn_id;

  obj_data->conn_counter ++;

  conn_id = g_new (guint, 1);
  *conn_id = obj_data->conn_counter;

  evd_dbus_agent_conn_data_ref (obj_conn_data->conn_data);

  g_hash_table_insert (obj_data->conns, conn_id, obj_conn_data);

  g_signal_connect (obj_conn_data->conn_data->conn,
                    "closed",
                    G_CALLBACK (evd_dbus_agent_on_object_connection_closed),
                    obj_data);

  g_object_ref (obj_conn_data->conn_data->conn);

  return conn_id;
}
