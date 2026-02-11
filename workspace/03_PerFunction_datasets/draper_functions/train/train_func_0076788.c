httpc_get(httpc_conn_t * conn, hresponse_t ** out, const char *urlstr)
{
  herror_t status;

  if ((status = httpc_talk_to_server(HTTP_REQUEST_GET, conn, urlstr)) != H_OK)
    return status;

  if ((status = hresponse_new_from_socket(&(conn->sock), out)) != H_OK)
    return status;

  return H_OK;
}
