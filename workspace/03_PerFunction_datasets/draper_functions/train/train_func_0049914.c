Param_index_from_handle(Param_table_type *table, int ParamHandle)
{
  int i;
  int index = -1;

  if(ParamHandle == REG_PARAM_HANDLE_NOTSET) return -1;


  for(i=0; i<table->max_entries; i++){

    if(table->param[i].handle == ParamHandle){

      index = i;
      break;
    }
  }

  return index;
}
