Curl_ssl_initsessions(struct SessionHandle *data, size_t amount)
{
  struct curl_ssl_session *session;

  if(data->state.session)

    return CURLE_OK;

  session = calloc(amount, sizeof(struct curl_ssl_session));
  if(!session)
    return CURLE_OUT_OF_MEMORY;


  data->set.ssl.max_ssl_sessions = amount;
  data->state.session = session;
  data->state.sessionage = 1;
  return CURLE_OK;
}
