j_obj(apr_pool_t *pool, char **val, apr_table_t *tl, char *name, int rec) {
  char *d = j_skip(*val);
  int rc;
  while(d && d[0]) {
    if(*d != '\"') {
      apr_table_add(tl, QOS_J_ERROR, "error while parsing object (missing string)");
      return HTTP_BAD_REQUEST;
    } else {

      char *v = NULL;
      char *thisname;
      d++;
      rc = j_string(pool, &d, tl, name, &v);
      if(rc != APR_SUCCESS) {
	return rc;
      }
      thisname = apr_pstrcat(pool, name, "_" , v, NULL);
      d = j_skip(d);
      if(!d || d[0] != ':') {
	apr_table_add(tl, QOS_J_ERROR, "error while parsing object (missing value/wrong delimiter)");
	return HTTP_BAD_REQUEST;
      }
      d++;
      rc = j_val(pool, &d, tl, thisname, rec);
      if(rc != APR_SUCCESS) {
	return rc;
      }
      d = j_skip(d);
      if(!d) {
	apr_table_add(tl, QOS_J_ERROR, "error while parsing object (unexpected end)");
	return HTTP_BAD_REQUEST;
      }
      if(d[0] == '}') {
	d++;
	*val = d;
	return APR_SUCCESS;
      } else if(d[0] == ',') {
	d = j_strchr(d, '"');
      } else {
	apr_table_add(tl, QOS_J_ERROR, "error while parsing object (unexpected end/wrong delimiter)");
	return HTTP_BAD_REQUEST;
      }
    }
  }
  return APR_SUCCESS;
}
