httpd_request_print(hrequest_t * req)
{
  hpair_t *pair;

  log_verbose1("++++++ Request +++++++++");
  log_verbose2(" Method : '%s'",
               (req->method == HTTP_REQUEST_POST) ? "POST" : "GET");
  log_verbose2(" Path   : '%s'", req->path);
  log_verbose2(" Spec   : '%s'",
               (req->version == HTTP_1_0) ? "HTTP/1.0" : "HTTP/1.1");
  log_verbose1(" Parsed query string :");

  for (pair = req->query; pair; pair = pair->next)
    log_verbose3(" %s = '%s'", pair->key, pair->value);

  log_verbose1(" Parsed header :");
  for (pair = req->header; pair; pair = pair->next)
    log_verbose3(" %s = '%s'", pair->key, pair->value);

  log_verbose1("++++++++++++++++++++++++");

  return;
}
