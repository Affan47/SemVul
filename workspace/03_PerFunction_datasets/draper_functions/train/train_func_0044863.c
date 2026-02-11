cmor_is_required_global_attribute(char *name, int table_id) {
  int i,j,n,req;
  char msg[CMOR_MAX_STRING];
  cmor_add_traceback("cmor_is_required_global_attribute");
  if (cmor_tables[table_id].required_gbl_att[0]=='\0') {
    cmor_pop_traceback();
    return 1;
  }

  n =strlen(cmor_tables[table_id].required_gbl_att);

  msg[0]='\0';
  i=0;
  j=0;
  req = 1;
  while (i<n) {
    while((cmor_tables[table_id].required_gbl_att[i]!=' ')&&(cmor_tables[table_id].required_gbl_att[i]!='\0'))  {
      msg[j]=cmor_tables[table_id].required_gbl_att[i];
      msg[j+1]='\0';
      j++;
      i++;
    }
    i++;
    j=0;
    if (strcmp(msg,name)==0) {
      req = 0;
      i=n;
    }
  }
  cmor_pop_traceback();
  return req;
}
