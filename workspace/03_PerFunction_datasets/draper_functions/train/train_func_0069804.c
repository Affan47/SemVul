conn_requests_requestotron (TpBaseConnection *self,
                            GHashTable *requested_properties,
                            ChannelRequestMethod method,
                            DBusGMethodInvocation *context)
{
  TP_BASE_CONNECTION_ERROR_IF_NOT_CONNECTED (self, context);


  conn_requests_check_basic_properties (self, requested_properties, method,
      context);
}
