json_object_double_to_json_string(struct json_object* jso,
					     struct printbuf *pb)
{

  char szBuffer[75];
  int ret = json_OGRFormatDouble( szBuffer, sizeof(szBuffer), jso->o.c_double, '.',
                                  (jso->_precision < 0) ? 15 : jso->_precision );
  if (ret < 0)
    return ret;
  return printbuf_memappend(pb, szBuffer, ret);
}
