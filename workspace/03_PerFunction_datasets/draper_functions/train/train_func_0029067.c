http_parser_parse_url(const char *buf, size_t buflen, int is_connect,
                      struct http_parser_url *u)
{
  enum state s;
  const char *p;
  enum http_parser_url_fields uf, old_uf;

  u->port = u->field_set = 0;
  s = is_connect ? s_req_host_start : s_req_spaces_before_url;
  uf = old_uf = UF_MAX;

  for (p = buf; p < buf + buflen; p++) {
    s = parse_url_char(s, *p);


    switch (s) {
      case s_dead:
        return 1;


      case s_req_schema_slash:
      case s_req_schema_slash_slash:
      case s_req_host_start:
      case s_req_host_v6_start:
      case s_req_host_v6_end:
      case s_req_port_start:
      case s_req_query_string_start:
      case s_req_fragment_start:
        continue;

      case s_req_schema:
        uf = UF_SCHEMA;
        break;

      case s_req_host:
      case s_req_host_v6:
        uf = UF_HOST;
        break;

      case s_req_port:
        uf = UF_PORT;
        break;

      case s_req_path:
        uf = UF_PATH;
        break;

      case s_req_query_string:
        uf = UF_QUERY;
        break;

      case s_req_fragment:
        uf = UF_FRAGMENT;
        break;

      default:
        assert(!"Unexpected state");
        return 1;
    }


    if (uf == old_uf) {
      u->field_data[uf].len++;
      continue;
    }

    u->field_data[uf].off = p - buf;
    u->field_data[uf].len = 1;

    u->field_set |= (1 << uf);
    old_uf = uf;
  }


  if (is_connect && u->field_set != ((1 << UF_HOST)|(1 << UF_PORT))) {
    return 1;
  }


  switch (s) {
  case s_req_host_v6_start:
  case s_req_host_v6:
  case s_req_host_v6_end:
  case s_req_host:
  case s_req_port_start:
    return 1;
  default:
    break;
  }

  if (u->field_set & (1 << UF_PORT)) {

    unsigned long v = strtoul(buf + u->field_data[UF_PORT].off, NULL, 10);


    if (v > 0xffff) {
      return 1;
    }

    u->port = (uint16_t) v;
  }

  return 0;
}
