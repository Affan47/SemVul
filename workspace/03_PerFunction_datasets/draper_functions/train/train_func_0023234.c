Increment_log_entry(Chk_log_type *log)
{
  int   i, j;
  int   new_size;
  void *dum_ptr;
  int   return_status = REG_SUCCESS;

  if (!log) return REG_FAILURE;


  if(++log->num_entries >= log->max_entries){

    new_size = log->max_entries + REG_INITIAL_CHK_LOG_SIZE;

    if( (dum_ptr = realloc(log->entry,
			   new_size*sizeof(Chk_log_entry_type))) ){

      log->entry = (Chk_log_entry_type *)dum_ptr;
      log->max_entries = new_size;


      for(i=log->num_entries; i<log->max_entries; i++){

	for(j=0; j<REG_MAX_NUM_STR_PARAMS; j++){
	  log->entry[i].param[j].handle = REG_PARAM_HANDLE_NOTSET;
	}
      }
    }
    else{
      fprintf(stderr, "STEER: Increment_log_entry: failed to allocate more "
	      "memory\n");
      log->num_entries--;
      return_status = REG_FAILURE;
    }
  }

  return return_status;
}
