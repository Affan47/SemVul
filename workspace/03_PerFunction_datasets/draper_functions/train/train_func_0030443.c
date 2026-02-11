qos_maxpost(request_rec *r, qos_srv_config *sconf, qos_dir_config *dconf) {
  if(r->subprocess_env) {
    const char *bytes = apr_table_get(r->subprocess_env, "QS_LimitRequestBody");
    if(bytes) {
      apr_off_t s;
#ifdef ap_http_scheme

      char *errp = NULL;
      if(APR_SUCCESS == apr_strtoff(&s, bytes, &errp, 10)) {
        return s;
      }
#else
      if((s = apr_atoi64(bytes)) >= 0) {
        return s;
      }
#endif
    }
  }
  if(dconf->maxpost != -1) {
    return dconf->maxpost;
  }
  return sconf->maxpost;
}
