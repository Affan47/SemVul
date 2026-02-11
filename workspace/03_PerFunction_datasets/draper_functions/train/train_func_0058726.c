cl_string_list_remove_string(cl_raw_list_t* list_p, char* string, int lock_list ) {
   int ret_val = CL_RETVAL_OK;
   int function_return = CL_RETVAL_UNKOWN_HOST_ERROR;
   cl_string_list_elem_t* elem = NULL;

   if (list_p == NULL || string == NULL) {
      return CL_RETVAL_PARAMS;
   }

   if (lock_list != 0) {

      if ( (ret_val = cl_raw_list_lock(list_p)) != CL_RETVAL_OK) {
         return ret_val;
      }
   }

   elem = cl_string_list_get_first_elem(list_p);
   while ( elem != NULL) {
      if (strcmp(elem->string,string) == 0 ) {

         cl_raw_list_remove_elem(list_p, elem->raw_elem);
         function_return = CL_RETVAL_OK;
         free(elem->string);
         free(elem);
         elem = NULL;
         break;
      }
      elem = cl_string_list_get_next_elem(elem);
   }

   if (lock_list != 0) {

      if ( (ret_val = cl_raw_list_unlock(list_p)) != CL_RETVAL_OK) {
         return ret_val;
      }
   }
   return function_return;
}
