Curl_http_connect(struct connectdata *conn, bool *done)
{
  struct SessionHandle *data;
  CURLcode result;

  data=conn->data;


  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {


    result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
                               conn->host.name,
                               conn->remote_port);
    if(CURLE_OK != result)
      return result;
  }

  if(!data->state.this_is_a_follow) {

    if (data->state.first_host)

      free(data->state.first_host);

    data->state.first_host = strdup(conn->host.name);
    if(!data->state.first_host)
      return CURLE_OUT_OF_MEMORY;
  }

  if(conn->protocol & PROT_HTTPS) {

    if(data->state.used_interface == Curl_if_multi) {
      result = Curl_https_connecting(conn, done);
      if(result)
        return result;
    }
    else {

      result = Curl_ssl_connect(conn, FIRSTSOCKET);
      if(result)
        return result;
      *done = TRUE;
    }
  }
  else {
    *done = TRUE;
  }

  return CURLE_OK;
}
