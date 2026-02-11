Curl_ossl_data_pending(const struct connectdata *conn,
                            int connindex)
{
  if(conn->ssl[connindex].handle)

    return (0 != SSL_pending(conn->ssl[connindex].handle)) ? TRUE : FALSE;
  else
    return FALSE;
}
