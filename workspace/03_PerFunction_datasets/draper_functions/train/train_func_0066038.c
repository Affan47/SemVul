test(char *URL)
{
  CURL *curl;
  CURLcode res=CURLE_OK;

  struct WriteThis pooh;

  pooh.readptr = data;
  pooh.sizeleft = strlen(data);

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }


  test_setopt(curl, CURLOPT_URL, URL);


  test_setopt(curl, CURLOPT_POST, 1L);

#ifdef CURL_DOES_CONVERSIONS

  test_setopt(curl, CURLOPT_TRANSFERTEXT, 1L);
#endif


  test_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)pooh.sizeleft);


  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);


  test_setopt(curl, CURLOPT_READDATA, &pooh);


  test_setopt(curl, CURLOPT_VERBOSE, 1L);


  test_setopt(curl, CURLOPT_HEADER, 1L);


  res = curl_easy_perform(curl);

test_cleanup:


  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}
