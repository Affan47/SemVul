hrequest_new(void)
{
  hrequest_t *req;

  if (!(req = (hrequest_t *) malloc(sizeof(hrequest_t)))) {

	  log_error1("malloc failed");
	  return NULL;
  }

  req->method = HTTP_REQUEST_GET;
  req->version = HTTP_1_1;
  req->query = NULL;
  req->header = NULL;
  req->in = NULL;
  req->attachments = NULL;
  req->content_type = NULL;

  return req;
}
