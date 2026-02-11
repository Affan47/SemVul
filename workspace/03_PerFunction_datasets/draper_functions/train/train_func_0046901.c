qos_crline(request_rec *r, const char *line) {
  char *string = "";
  const char *pos = line;
  while(pos && pos[0]) {
    int len = strlen(pos);
    if(len > QOS_ALERT_LINE_LEN) {
      string = apr_pstrcat(r->pool, string,
                           apr_psprintf(r->pool, "%.*s", QOS_ALERT_LINE_LEN, pos), "\n", NULL);
      pos = &pos[QOS_ALERT_LINE_LEN];
    } else {
      string = apr_pstrcat(r->pool, string, pos, NULL);
      pos = NULL;
    }
  }
  return string;
}
