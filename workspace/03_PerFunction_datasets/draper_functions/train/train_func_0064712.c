cmor_has_required_global_attributes(int table_id) {
  int i,j,n,found;
  char msg[CMOR_MAX_STRING];
  char msg2[CMOR_MAX_STRING];
  char ctmp[CMOR_MAX_STRING];
  char expt_id[CMOR_MAX_STRING];
  cmor_add_traceback("cmor_has_required_global_attributes");
  if (cmor_tables[table_id].required_gbl_att[0]=='\0') {
    cmor_pop_traceback();
    return;
  }
  cmor_get_cur_dataset_attribute("experiment_id",expt_id);

  for (j=0;j<=cmor_tables[table_id].nexps;j++) {
    if (strcmp(expt_id,cmor_tables[table_id].expt_ids[j])==0) {
      strncpy(expt_id,cmor_tables[table_id].sht_expt_ids[j],CMOR_MAX_STRING);
      break;
    }
  }


  n =strlen(cmor_tables[table_id].required_gbl_att);

  msg[0]='\0';
  j=0;
  i=0;
  msg2[0]='\0';
  while (i<n) {
    while((cmor_tables[table_id].required_gbl_att[i]!=' ') && (cmor_tables[table_id].required_gbl_att[i]!='\0'))  {
      msg[j]=cmor_tables[table_id].required_gbl_att[i];
      msg[j+1]='\0';
      j++;
      i++;
    }
    i++;
    found = 0 ;


    for (j=0;j<cmor_current_dataset.nattributes;j++) {
      if (strcmp(msg,cmor_current_dataset.attributes_names[j])==0) {
	cmor_get_cur_dataset_attribute(msg,ctmp);
	if (strcmp(ctmp,"not specified")!=0) {
	  found = 1;
	  break;
	}
      }
    }


    if (found == 0) {
      snprintf(ctmp,CMOR_MAX_STRING,"Required global attribute %s is missing please check call(s) to cmor_dataset and/or cmor_set_cur_dataset_attribute",msg);
      cmor_handle_error(ctmp,CMOR_CRITICAL);
    }
    strncpy(msg2,msg,CMOR_MAX_STRING);
    j=0;
  }
  cmor_pop_traceback();
  return;
}
