Curl_pretransfer(struct SessionHandle *data)
{
  CURLcode res;
  if(!data->change.url)

    return CURLE_URL_MALFORMAT;


  res = Curl_ssl_initsessions(data, data->set.ssl.numsessions);
  if(res)
    return res;

  data->set.followlocation=0;
  data->state.this_is_a_follow = FALSE;
  data->state.errorbuf = FALSE;

  data->state.authproblem = FALSE;
  data->state.authhost.want = data->set.httpauth;
  data->state.authproxy.want = data->set.proxyauth;

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)


  if(data->change.cookielist) {
    struct curl_slist *list = data->change.cookielist;
    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
    while(list) {
      data->cookies = Curl_cookie_init(data,
                                       list->data,
                                       data->cookies,
                                       data->set.cookiesession);
      list = list->next;
    }
    Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    curl_slist_free_all(data->change.cookielist);
    data->change.cookielist = NULL;
  }
#endif


  data->state.allow_port = TRUE;

#if defined(HAVE_SIGNAL) && defined(SIGPIPE) && !defined(HAVE_MSG_NOSIGNAL)


  if(!data->set.no_signal)
    data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
#endif

  Curl_initinfo(data);
  Curl_pgrsStartNow(data);

  return CURLE_OK;
}
