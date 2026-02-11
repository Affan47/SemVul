voy_request_header_create(GPtrArray *request_query, RequestHeader *request_header) {
  int i;
  gchar* request_params;


  if (request_query->len > 0) {
    request_params = (gchar*) g_ptr_array_index(request_query, 0);
    voy_request_header_set_request(request_params, request_header);
    g_free(request_params);
  }


  for (i = 1; i < request_query->len; i++) {
    gchar **request_fragment;
    gchar *tmp;
    tmp = (gchar*) g_ptr_array_index(request_query, i);


    request_fragment = g_strsplit(tmp, ": ", 2);
    voy_request_header_set(request_fragment[0], g_strstrip(request_fragment[1]), request_header);

    g_strfreev(request_fragment);
    g_free(tmp);
  }
}
