httpd_get_postdata(httpd_conn_t * conn, hrequest_t * req, long *received,
                   long max)
{
  char *content_length_str;
  long content_length = 0;
  unsigned char *postdata = NULL;

  if (req->method == HTTP_REQUEST_POST)
  {

    content_length_str =
      hpairnode_get_ignore_case(req->header, HEADER_CONTENT_LENGTH);

    if (content_length_str != NULL)
      content_length = atol(content_length_str);

  }
  else
  {
    log_warn1("Not a POST method");
    return NULL;
  }

  if (content_length > max && max != -1)
    return NULL;

  if (content_length == 0)
  {
    *received = 0;
    if (!(postdata = (char *) malloc(1)))
    {

      log_error1("malloc failed");
      return NULL;
    }
    postdata[0] = '\0';
    return postdata;
  }
  if (!(postdata = (unsigned char *) malloc(content_length + 1)))
  {
    log_error1("malloc failed");
    return NULL;
  }
  if (http_input_stream_read(req->in, postdata, (int) content_length) > 0)
  {
    *received = content_length;
    postdata[content_length] = '\0';
    return postdata;
  }
  free(postdata);
  return NULL;
}
