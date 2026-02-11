url_allowed_host(struct http_request* req) {
  u32 i;

  for (i=0;i<num_allow_domains;i++) {

    if (allow_domains[i][0] == '.') {

      u8* pos = inl_strcasestr(req->host, allow_domains[i]);

      if (pos && strlen((char*)req->host) ==
          strlen((char*)allow_domains[i]) + (pos - req->host))
        return 1;

    } else
      if (!strcasecmp((char*)req->host, (char*)allow_domains[i]))
        return 1;

  }

  return 0;
}
