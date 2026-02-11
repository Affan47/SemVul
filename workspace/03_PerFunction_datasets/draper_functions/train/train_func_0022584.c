clean_handle(void *handle) {
  char *url;
  CURLcode code = curl_easy_getinfo(handle, CURLINFO_PRIVATE, &url);
  if (code == CURLE_OK) {
    URL url2(url);

  }
  curl_multi_remove_handle(m_handle, handle);

  curl_easy_cleanup(handle);

}
