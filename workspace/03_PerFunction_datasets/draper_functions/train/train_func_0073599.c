bgav_rtsp_close(bgav_rtsp_t * r, int teardown)
  {
  if(teardown && (r->fd >= 0))
    rtsp_send_request(r,"TEARDOWN",r->url, NULL);

  bgav_http_header_destroy(r->answers);
  bgav_http_header_destroy(r->request_fields);
  bgav_sdp_free(&r->sdp);
  if(r->url) free(r->url);
  if(r->session) free(r->session);

  if(r->fd > 0)
    closesocket(r->fd);

  free(r);
  }
