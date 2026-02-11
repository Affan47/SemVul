curl_multi_add_handle(CURLM *multi_handle,
                                CURL *easy_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;


  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;


  if(!GOOD_EASY_HANDLE(easy_handle))
    return CURLM_BAD_EASY_HANDLE;


  easy = (struct Curl_one_easy *)malloc(sizeof(struct Curl_one_easy));
  if(!easy)
    return CURLM_OUT_OF_MEMORY;


  memset(easy, 0, sizeof(struct Curl_one_easy));


  easy->easy_handle = easy_handle;
  multistate(easy, CURLM_STATE_INIT);


  easy->easy_handle->hostcache = multi->hostcache;


  easy->next = multi->easy.next;
  easy->prev = &multi->easy;


  multi->easy.next = easy;


  if(easy->next)
    easy->next->prev = easy;

  Curl_easy_addmulti(easy_handle, multi_handle);


  multi->num_easy++;

  return CURLM_OK;
}
