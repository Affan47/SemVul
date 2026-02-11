getinfo_slist(struct SessionHandle *data, CURLINFO info,
                              struct curl_slist **param_slistp)
{
  union {
    struct curl_certinfo * to_certinfo;
    struct curl_slist    * to_slist;
  } ptr;

  switch(info) {
  case CURLINFO_SSL_ENGINES:
    *param_slistp = Curl_ssl_engines_list(data);
    break;
  case CURLINFO_COOKIELIST:
    *param_slistp = Curl_cookie_list(data);
    break;
  case CURLINFO_CERTINFO:


    ptr.to_certinfo = &data->info.certs;
    *param_slistp = ptr.to_slist;
    break;
  case CURLINFO_TLS_SESSION:
    {
      struct curl_tlssessioninfo **tsip = (struct curl_tlssessioninfo **)
                                          param_slistp;
      struct curl_tlssessioninfo *tsi = &data->tsi;
      struct connectdata *conn = data->easy_conn;
      unsigned int sockindex = 0;
      void *internals = NULL;

      *tsip = tsi;
      tsi->backend = CURLSSLBACKEND_NONE;
      tsi->internals = NULL;

      if(!conn)
        break;


      while((sockindex < sizeof(conn->ssl) / sizeof(conn->ssl[0])) &&
            (!conn->ssl[sockindex].use))
        sockindex++;

      if(sockindex == sizeof(conn->ssl) / sizeof(conn->ssl[0]))
        break;


#ifdef USE_SSLEAY
      internals = conn->ssl[sockindex].ctx;
#endif
#ifdef USE_GNUTLS
      internals = conn->ssl[sockindex].session;
#endif
#ifdef USE_NSS
      internals = conn->ssl[sockindex].handle;
#endif
#ifdef USE_GSKIT
      internals = conn->ssl[sockindex].handle;
#endif
      if(internals) {
        tsi->backend = Curl_ssl_backend();
        tsi->internals = internals;
      }


    }
    break;
  default:
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }
  return CURLE_OK;
}
