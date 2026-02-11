Curl_freeset(struct SessionHandle *data)
{

  enum dupstring i;
  for(i=(enum dupstring)0; i < STRING_LAST; i++) {
    Curl_safefree(data->set.str[i]);
  }

  if(data->change.referer_alloc) {
    Curl_safefree(data->change.referer);
    data->change.referer_alloc = FALSE;
  }
  data->change.referer = NULL;
}
