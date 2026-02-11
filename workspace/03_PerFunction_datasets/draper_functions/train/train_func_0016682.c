Curl_ssl_getsessionid(struct connectdata *conn,
                          void **ssl_sessionid,
                          size_t *idsize)
{
  struct curl_ssl_session *check;
  struct SessionHandle *data = conn->data;
  size_t i;
  long *general_age;
  bool no_match = TRUE;

  *ssl_sessionid = NULL;

  if(!conn->ssl_config.sessionid)

    return TRUE;


  if(SSLSESSION_SHARED(data)) {
    Curl_share_lock(data, CURL_LOCK_DATA_SSL_SESSION, CURL_LOCK_ACCESS_SINGLE);
    general_age = &data->share->sessionage;
  }
  else
    general_age = &data->state.sessionage;

  for(i = 0; i < data->set.ssl.max_ssl_sessions; i++) {
    check = &data->state.session[i];
    if(!check->sessionid)

      continue;
    if(Curl_raw_equal(conn->host.name, check->name) &&
       (conn->remote_port == check->remote_port) &&
       Curl_ssl_config_matches(&conn->ssl_config, &check->ssl_config)) {

      (*general_age)++;
      check->age = *general_age;
      *ssl_sessionid = check->sessionid;
      if(idsize)
        *idsize = check->idsize;
      no_match = FALSE;
      break;
    }
  }


  if(SSLSESSION_SHARED(data))
    Curl_share_unlock(data, CURL_LOCK_DATA_SSL_SESSION);

  return no_match;
}
