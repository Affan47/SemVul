parse_http_request(char *buf, int len, struct mg_request_info *ri) {
  int result = parse_http_message(buf, len, ri);
  if (result > 0 &&
      is_valid_http_method(ri->request_method) &&
      !strncmp(ri->http_version, "HTTP/", 5)) {
    ri->http_version += 5;
  } else {
    result = -1;
  }
  return result;
}
