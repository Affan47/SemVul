mod_enc_parse(request_rec *r) {
  encoding_config *conf, *dconf, *sconf;

  const char *pass;
  char       *user;
  char       *buff;

  sconf = ap_get_module_config(r->server->module_config, &encoding_module);
  dconf = ap_get_module_config(r->per_dir_config, &encoding_module);
   conf = config_merge(r->pool, sconf, dconf);

  if (conf->enable_function != ENABLE_FLAG_ON) {
    return DECLINED;
  }


  if (conf->strip_msaccount == STRIP_FLAG_ON) {


    if (ap_get_basic_auth_pw(r, &pass) != OK)
      return DECLINED;


    if ((user = index(r->user, '\\')) == NULL)
      return DECLINED;


    if (*(user + 1)) {
      buff = ap_pbase64encode(r->pool,
                              apr_psprintf(r->pool, "%s:%s", user + 1, pass));
      apr_table_set(r->headers_in, "Authorization",
                   apr_pstrcat(r->pool, "Basic ", buff, NULL));

      ap_get_basic_auth_pw(r, &pass);
    }
  }

  return DECLINED;
}
