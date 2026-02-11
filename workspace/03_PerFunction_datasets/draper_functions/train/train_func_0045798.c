voy_request_header_set_request(gchar * const request_string, RequestHeader *request_header) {
  g_assert(request_string);
  gchar **request_params;
  request_params = g_strsplit(request_string, " ", 0);
  voy_request_header_set("Method", g_strstrip(g_strdup(request_params[0])), request_header);
  voy_request_header_set("URL", g_strstrip(g_strdup(request_params[1])), request_header);
  voy_request_header_set("HTTP-Version", g_strstrip(g_strdup(request_params[2])), request_header);
  g_strfreev(request_params);
}
