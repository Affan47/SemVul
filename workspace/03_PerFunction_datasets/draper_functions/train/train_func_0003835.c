sinfo_table_get_index_of_val(cpl_table* t,
                             const char* name,
                             double val,
                             cpl_type type)
{

  int i=0;
  int result=0;
  int nrow=0;
  int* pi=NULL;
  float* pf=NULL;
  double* pd=NULL;

  if(t == NULL) {
   cpl_error_set(cpl_func, CPL_ERROR_NULL_INPUT);
   return result;
  }

  nrow=cpl_table_get_nrow(t);
  switch(type) {

  case CPL_TYPE_INT:
    pi=cpl_table_get_data_int(t,name);
    for(i=0;i<nrow;i++) {
      if(pi[i]==(int)val) result=i;
    }
    break;
  case CPL_TYPE_FLOAT:
    pf=cpl_table_get_data_float(t,name);
    for(i=0;i<nrow;i++) {
      if(pf[i]==(float)val) result=i;
    }
    break;
  case CPL_TYPE_DOUBLE:
    pd=cpl_table_get_data_double(t,name);
    for(i=0;i<nrow;i++) {
      if(pd[i]==val) result=i;
    }
    break;
  default:
    sinfo_msg_error("Wrong column type");
   cpl_error_set(cpl_func, CPL_ERROR_TYPE_MISMATCH);
   return result;

  }
  return result;
}
