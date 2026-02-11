infc_browser_get_chat_request_foreach_func(InfcRequest* request,
                                           gpointer user_data)
{
  InfcBrowserIterGetNodeRequestForeachData* data;

  data = (InfcBrowserIterGetNodeRequestForeachData*)user_data;
  g_assert(INFC_IS_NODE_REQUEST(request));


  g_assert(data->result == NULL);


  data->result = INFC_NODE_REQUEST(request);
}
