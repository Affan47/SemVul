Curl_wildcard_init(struct WildcardData *wc)
{
  DEBUGASSERT(wc->filelist == NULL);


  wc->filelist = Curl_llist_alloc(Curl_fileinfo_dtor);
  if(!wc->filelist) {;
    return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}
