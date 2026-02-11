qos_load_rules(apr_pool_t *pool, apr_table_t *ruletable,
                           const char *httpdconf, const char *command, int option) {
  FILE *f = fopen(httpdconf, "r");
  char line[MAX_LINE];
  if(f == NULL) {
    fprintf(stderr, "ERROR, could not open %s\n", httpdconf);
    exit(1);
  }
  while(!qos_fgetline(line, sizeof(line), f)) {

    char *p = strstr(line, command);
    if(p) {
      p[0] = '\0';
      p++;
    }
    if(p && (strchr(line, '#') == NULL)) {
      p = strchr(p, ' ');
      if(p) {
        while(p[0] == ' ') p++;
        p = strchr(p, ' ');
        if(p) {
          while(p[0] == ' ') p++;
          p = strchr(p, ' ');
          if(p) {
            while(p[0] == ' ') p++;
            if(m_verbose > 1) {
              printf("load %s\n", p);
            }
            {
              const char *errptr = NULL;
              char *pattern;
              pcre *pcre_test;
              pcre_extra *extra;
              qs_rule_t *rs;
              if(p[0] == '"') {
                int fl = strlen(p)-2;
                pattern = apr_psprintf(pool, "%.*s", fl, &p[1]);
              } else {
                int fl = strlen(p);
                pattern = apr_psprintf(pool, "%.*s", fl, p);
              }
              pcre_test = qos_pcre_compile(pattern, option);
              extra = pcre_study(pcre_test, 0, &errptr);
              rs = apr_pcalloc(pool, sizeof(qs_rule_t));
              rs->pcre = pcre_test;
              rs->extra = extra;
              apr_table_setn(ruletable, pattern, (char *)rs);
            }
          }
        }
      }
    }
  }
  fclose(f);
}
