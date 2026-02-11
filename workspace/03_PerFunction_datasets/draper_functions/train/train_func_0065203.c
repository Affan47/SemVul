evd_jsonrpc_on_method_called (EvdJsonrpc  *self,
                              JsonObject  *msg,
                              gpointer     context,
                              GError     **error)
{
  JsonNode *node;
  JsonNode *args;
  const gchar *method_name;

  InvocationData *inv_data;
  guint id;
  gchar *id_st;
  JsonNode *id_node;

  node = json_object_get_member (msg, "method");
  method_name = json_node_get_string (node);
  if (! JSON_NODE_HOLDS_VALUE (node) ||
      method_name == NULL)
    {
      g_set_error_literal (error,
                           G_IO_ERROR,
                           G_IO_ERROR_INVALID_DATA,
                           "Method name in JSON-RPC must be a valid string");
      return FALSE;
    }

  args = json_object_get_member (msg, "params");
  if (! JSON_NODE_HOLDS_ARRAY (args))
    {
      g_set_error_literal (error,
                           G_IO_ERROR,
                           G_IO_ERROR_INVALID_DATA,
                           "Params in a JSON-RPC request must be an array");
      return FALSE;
    }

  id_node = json_object_dup_member (msg, "id");
  if (json_node_is_null (id_node))
    {


      json_node_free (id_node);

      return TRUE;
    }

  inv_data = g_slice_new0 (InvocationData);
  inv_data->remote_id = id_node;
  inv_data->context = context;

  self->priv->invocation_counter++;
  id = self->priv->invocation_counter;
  id_st = g_strdup_printf ("%u", id);

  g_hash_table_insert (self->priv->invocations, id_st, inv_data);

  if (self->priv->method_call_cb != NULL)
    {
      self->priv->method_call_cb (self,
                                  method_name,
                                  args,
                                  id,
                                  context,
                                  self->priv->method_call_cb_user_data);
    }

  return TRUE;
}
