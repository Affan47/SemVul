CDE_end_rmdir(struct tcb* tcp, int input_buffer_arg_index) {
  if (CDE_verbose_mode) {
    printf("[%d] END rmdir*\n", tcp->pid);
  }

  if (CDE_exec_mode) {

  }
  else {
    if (tcp->u_rval == 0) {
      char* dirname_arg = strcpy_from_child(tcp, tcp->u_arg[input_buffer_arg_index]);
      char* redirected_path =
        redirect_filename_into_cderoot(dirname_arg, tcp->current_dir, tcp);
      if (redirected_path) {
        rmdir(redirected_path);
        free(redirected_path);
      }
      free(dirname_arg);
    }
  }
}
