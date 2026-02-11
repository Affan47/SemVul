HTTPExchange_read_response_headers(HTTPExchange * exchange) {

  int result = HTTPExchange_flush_request(exchange);
  if (result != 0) {
    return result;
  }

  result = HTTPMessage_read_start_line_and_headers(exchange->response_message);
  if (result != 0) {
    return result;
  }


  const char * status_line = HTTPMessage_get_start_line(exchange->response_message);
  const char * p = status_line;


  if (! str_starts_with(p, "HTTP/")) {
    return -1;
  }
  p += 5;
  const char * start = p;
  skip_digits(&p);
  if (start == p) {
    return -1;
  }
  if (*p != '.') {
    return -1;
  }
  p++;
  start = p;
  skip_digits(&p);
  if (start == p) {
    return -1;
  }
  if (*p != ' ') {
    return -1;
  }
  exchange->response_http_version = xstrndup(status_line, p - status_line);


  p++;


  start = p;
  skip_digits(&p);
  if (p - start != 3) {
    return -1;
  }
  if (*p != ' ') {
    return -1;
  }
  exchange->status_code = strtoul(start, NULL, 10);

  return 0;
}
