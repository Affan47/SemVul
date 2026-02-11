ap_manager_free(ap_manager_t* man)
{
  if (man->count>1){
    man->count--;
  }
  else {
    if (man->internal != NULL){
      man->internal_free(man->internal);
      man->internal = NULL;
    }
    ap_result_clear(&man->result);
    free(man);
  }
}
