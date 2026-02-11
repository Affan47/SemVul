Delete_log_entry_struct(struct log_entry_struct *log)
{
  struct log_entry_struct *dum_ptr;

  while(log){

    xmlFree(log->key);

    Delete_chk_log_entry_struct(log->first_chk_log);
    Delete_param_struct(log->first_param_log);

    dum_ptr = log->next;
    free(log);
    log = dum_ptr;
  }
}
