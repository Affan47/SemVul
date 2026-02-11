jsonrpc_on_method_call (EvdJsonrpc  *rpc,
                        const gchar *method_name,
                        JsonNode    *params,
                        guint        invocation_id,
                        gpointer     context,
                        gpointer     user_data)
{
  EvdJsonrpcHttpServer *self = EVD_JSONRPC_HTTP_SERVER (user_data);
  EvdHttpConnection *conn = EVD_HTTP_CONNECTION (context);

  if (self->priv->method_call_cb != NULL)
    {
      EvdHttpRequest *req;

      req = evd_http_connection_get_current_request (conn);

      g_object_ref (conn);
      self->priv->method_call_cb (self,
                                  method_name,
                                  params,
                                  invocation_id,
                                  conn,
                                  req,
                                  self->priv->method_call_user_data);
    }
  else
    {
      const gchar *err_st = "No handler for method calls";

      evd_web_service_respond (EVD_WEB_SERVICE (self),
                               conn,
                               SOUP_STATUS_INTERNAL_SERVER_ERROR,
                               self->priv->headers,
                               err_st,
                               strlen (err_st),
                               NULL);
    }
}
