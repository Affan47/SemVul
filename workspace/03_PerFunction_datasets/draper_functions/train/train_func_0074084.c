fix_request(request *r) {
  if(!r->http) r->http = strdup("HTTP/1.0");
  if(!r->file) r->file = strdup(".");
}
