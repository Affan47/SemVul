mod_enc_convert(request_rec *r) {
  encoding_config  *conf, *dconf, *sconf;

  const char      *oenc;
  apr_array_header_t    *ienc;
  void           **list;

  iconv_t cd;

  int i;


  sconf = ap_get_module_config(r->server->module_config, &encoding_module);
  dconf = ap_get_module_config(r->per_dir_config, &encoding_module);
   conf = config_merge(r->pool, sconf, dconf);

  if (conf->enable_function != ENABLE_FLAG_ON) {
    return DECLINED;
  }

  oenc = conf->server_encoding ? conf->server_encoding : "UTF-8";
  ienc = get_client_encoding(r, conf->client_encoding,
			     apr_table_get(r->headers_in, "User-Agent"));

  if (conf->default_encoding)
    apr_array_cat(ienc, conf->default_encoding);

  list = (void **)ienc->elts;


  for (i = 0 ; i < ienc->nelts ; i++) {


    if ((cd = iconv_open(oenc, list[i])) == (iconv_t)(-1))
      continue;


    if (iconv_header(r, cd) == 0) {
      iconv_close(cd);
      return DECLINED;
    }


    iconv_close(cd);
  }


  return DECLINED;
}
