xsh_parameters_create_from_drs_table(const cpl_table* tab)
{

   cpl_parameterlist* result=NULL;
   int nrow=0;
   int i=0;
   const char*  svalue=NULL;
   int    ivalue=0;
   float  fvalue=0;
   double dvalue=0;
   bool bvalue=0;

   const char* rec_id=NULL;
   const char* pname=NULL;
   const char* ptype=NULL;
   const char* phelp=NULL;


   XSH_ASSURE_NOT_NULL_MSG(tab,"Null input DRS tab");
   nrow=cpl_table_get_nrow(tab);
   result=cpl_parameterlist_new();
   for(i=0;i<nrow;i++) {
      check(rec_id=cpl_table_get_string(tab,"recipe",i));
      check(pname=cpl_table_get_string(tab,"param_name",i));
      check(ptype=cpl_table_get_string(tab,"param_type",i));
      check(phelp=cpl_table_get_string(tab,"param_help",i));

     if (strcmp(ptype,"int") == 0) {
       check(ivalue=atoi(cpl_table_get_string(tab,"param_value",i)));
         check(xsh_parameters_new_int(result,rec_id,pname,ivalue,phelp));
      }
      else if (strcmp(ptype,"float") == 0) {
	fvalue=atof(cpl_table_get_string(tab,"param_value",i));
         xsh_parameters_new_float(result,rec_id,pname,fvalue,phelp);
      }
      else if (strcmp(ptype,"double") == 0) {
	dvalue=atof(cpl_table_get_string(tab,"param_value",i));
         xsh_parameters_new_double(result,rec_id,pname,dvalue,phelp);
      }
      else if (strcmp(ptype,"string") == 0) {
         svalue=cpl_table_get_string(tab,"param_value",i);
         xsh_parameters_new_string(result,rec_id,pname,svalue,phelp);
      }
      else if (strcmp(ptype,"bool") == 0) {
	bvalue=atoi(cpl_table_get_string(tab,"param_value",i));
         xsh_parameters_new_bool(result,rec_id,pname,bvalue,phelp);
      }
      else {
         xsh_msg_error("DRS table parameter type %s not supported!",ptype);
         return NULL;
      }
   }

  cleanup:
   return result;
}
