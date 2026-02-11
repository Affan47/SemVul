updateUrl(apr_pool_t *pool, char *R, char *S, long tmems) {
  url_rec_t *url_rec;
  char *marker;
  if(R == NULL) {
    return;
  }
  if(!isalpha(R[0])) {
    fprintf(stdout, "A(%ld)", m_lines);
    return;
  }
  marker = strchr(R, ' ');
  if(marker == NULL) {
    fprintf(stdout, "E(%ld)", m_lines);
    return;
  }
  marker[0] = ';';
  marker = strrchr(R, ' ');
  if(marker) {
    marker[0] = '\0';
  }
  marker = strchr(R, '?');
  if(marker) {
    marker[0] = '\0';
  }
  if(m_offline_url_cropped) {
    char *root = strchr(R, '/');
    marker = strrchr(R, '/');
    if(marker && marker != root) {
      marker[0] = '\0';
    }
  }
  url_rec = (url_rec_t *)apr_table_get(m_url_entries, R);
  if(url_rec == NULL) {
    if(apr_table_elts(m_url_entries)->nelts >= MAX_CLIENT_ENTRIES) {

      if(!m_max_entries) {
        fprintf(stderr, "\nreached max url entries (%d)\n", MAX_CLIENT_ENTRIES);
        m_max_entries = 1;
      }
      return;
    }
    url_rec = apr_pcalloc(pool, sizeof(url_rec_t));
    url_rec->request_count = 0;
    url_rec->status_1 = 0;
    url_rec->status_2 = 0;
    url_rec->status_3 = 0;
    url_rec->status_4 = 0;
    url_rec->status_5 = 0;
    url_rec->duration_count_ms = 0;
    apr_table_setn(m_url_entries, apr_pstrdup(pool, R), (char *)url_rec);
  }
  url_rec->request_count++;
  if(S[0] == '1') {
    url_rec->status_1++;
  } else if(S[0] == '1') {
    url_rec->status_1++;
  } else if(S[0] == '2') {
    url_rec->status_2++;
  } else if(S[0] == '3') {
    url_rec->status_3++;
  } else if(S[0] == '4') {
    url_rec->status_4++;
  } else if(S[0] == '5') {
    url_rec->status_5++;
  }
  url_rec->duration_count_ms += tmems;
}
