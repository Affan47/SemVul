bgav_rtsp_request_describe(bgav_rtsp_t *rtsp, int * got_redirected)
  {
  int content_length;
  const char * var;
  char * buf = NULL;


  if(!rtsp_send_request(rtsp, "DESCRIBE", rtsp->url, got_redirected))
    goto fail;

  if(got_redirected && *got_redirected)
    {
    return 1;
    }
  var = bgav_http_header_get_var(rtsp->answers, "Content-Length");
  if(!var)
    goto fail;

  content_length = atoi(var);

  buf = malloc(content_length+1);

  if(bgav_read_data_fd(rtsp->opt, rtsp->fd, (uint8_t*)buf,
                       content_length, rtsp->opt->read_timeout) <
     content_length)
    {
    bgav_log(rtsp->opt, BGAV_LOG_ERROR, LOG_DOMAIN,
             "Reading session description failed");
    goto fail;
    }

  buf[content_length] = '\0';

  if(!bgav_sdp_parse(rtsp->opt, buf, &rtsp->sdp))
    goto fail;


  free(buf);

  return 1;

  fail:

  if(buf)
    free(buf);
  return 0;
  }
