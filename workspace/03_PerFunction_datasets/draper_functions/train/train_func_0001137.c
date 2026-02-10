cl_fd_list_cleanup(cl_raw_list_t **list_p) {
   cl_fd_list_elem_t* elem = NULL;

   elem = cl_fd_list_get_first_elem(*list_p);
   if (elem != NULL) {
      CL_LOG(CL_LOG_WARNING, "The list was NOT empty. Unregister all external file descriptors before cleanup next time, please");
   }

   while(elem){
      cl_fd_list_unregister_fd(*list_p, elem, 1);
      elem = cl_fd_list_get_next_elem(elem);
   }

   return cl_raw_list_cleanup(list_p);
}
