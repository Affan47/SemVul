qos_reslove_variable(apr_pool_t *p, apr_table_t *vars, char **string) {
  int i;
  int start;
  int line_end;
  char *var_name;
  char *new_line = *string;
  char *line = *string;
  const char *val;

 once_again:
  i = 0;
  while(line[i] != 0) {
    if((line[i] == '$') && (line[i+1] == '{')) {
      line_end = i;
      i=i+2;
      start = i;
      while((line[i] != 0) && (line[i] != '}')) {
        i++;
      }
      if(line[i] != '}') {

        break;
      } else {
        var_name = apr_pstrndup(p, &line[start], i - start);
        val = apr_table_get(vars, var_name);
        if(val) {
          line[line_end] = 0;
          i++;
          new_line = apr_pstrcat(p, line, val, &line[i], NULL);
          line = new_line;
          goto once_again;
        }
      }
    }
    i++;
  }
  if(!new_line[0] || strstr(new_line, "${")) {
    return 0;
  }
  *string = new_line;
  return 1;
}
