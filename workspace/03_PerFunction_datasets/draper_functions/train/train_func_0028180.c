tool_header_cb(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  struct HdrCbData *hdrcbdata = userdata;
  struct OutStruct *outs = hdrcbdata->outs;
  struct OutStruct *heads = hdrcbdata->heads;
  const char *str = ptr;
  const size_t cb = size * nmemb;
  const char *end = (char*)ptr + cb;


  size_t failure = (size * nmemb) ? 0 : 1;

  if(!heads->config)
    return failure;

#ifdef DEBUGBUILD
  if(size * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
    warnf(heads->config, "Header data exceeds single call write limit!\n");
    return failure;
  }
#endif


  if(heads->config->headerfile && heads->stream) {
    size_t rc = fwrite(ptr, size, nmemb, heads->stream);
    if(rc != cb)
      return rc;
  }


  if(hdrcbdata->honor_cd_filename &&
     (cb > 20) && checkprefix("Content-disposition:", str)) {
    const char *p = str + 20;


    for(;;) {
      char *filename;
      size_t len;

      while(*p && (p < end) && !ISALPHA(*p))
        p++;
      if(p > end - 9)
        break;

      if(memcmp(p, "filename=", 9)) {

        while((p < end) && (*p != ';'))
          p++;
        continue;
      }
      p += 9;


      len = (ssize_t)cb - (p - str);
      filename = parse_filename(p, len);
      if(filename) {
        outs->filename = filename;
        outs->alloc_filename = TRUE;
        outs->is_cd_filename = TRUE;
        outs->s_isreg = TRUE;
        outs->fopened = FALSE;
        outs->stream = NULL;
        hdrcbdata->honor_cd_filename = FALSE;
        break;
      }
      else
        return failure;
    }
  }

  return cb;
}
