cl_host_alias_list_remove_host(cl_raw_list_t* list_p, cl_host_alias_list_elem_t* element, int lock_list) {
   cl_host_alias_list_elem_t* elem = NULL;
   int ret_val = CL_RETVAL_OK;
   int function_return = CL_RETVAL_UNKNOWN;

   if (  list_p == NULL || element == NULL) {
      return CL_RETVAL_PARAMS;
   }

   if (lock_list != 0) {

      if ( (ret_val = cl_raw_list_lock(list_p)) != CL_RETVAL_OK) {
         return ret_val;
      }
   }

   elem = cl_host_alias_list_get_first_elem(list_p);
   while ( elem != NULL) {
      if (elem == element) {

         cl_raw_list_remove_elem(list_p, elem->raw_elem);
         function_return = CL_RETVAL_OK;
         free(elem->local_resolved_hostname);
         free(elem->alias_name);
         free(elem);
         elem = NULL;
         break;
      }
      elem = cl_host_alias_list_get_next_elem(elem);
   }

   if (lock_list != 0) {

      if ( (ret_val = cl_raw_list_unlock(list_p)) != CL_RETVAL_OK) {
         return ret_val;
      }
   }
   return function_return;
}
