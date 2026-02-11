cl_thread_list_get_thread_by_name(cl_raw_list_t* list_p, char* thread_name) {
   cl_thread_list_elem_t* elem = NULL;
   cl_thread_settings_t* thread_config = NULL;

   if (thread_name == NULL) {
      return NULL;
   }

   for (elem = cl_thread_list_get_first_elem(list_p); elem != NULL ; elem = cl_thread_list_get_next_elem(elem)) {
      if( strcmp(elem->thread_config->thread_name,thread_name) == 0) {
         thread_config = elem->thread_config;
         return thread_config;
      }
   }
   return thread_config;
}
