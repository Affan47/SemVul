CDE_begin_file_unlink(struct tcb* tcp) {
  char* filename = strcpy_from_child(tcp, tcp->u_arg[0]);

  if (CDE_verbose_mode) {
    printf("[%d] BEGIN unlink '%s'\n", tcp->pid, filename);
  }

  if (CDE_exec_mode) {
    modify_syscall_single_arg(tcp, 1, filename);
  }
  else {
    char* redirected_path = redirect_filename_into_cderoot(filename, tcp->current_dir, tcp);
    if (redirected_path) {
      unlink(redirected_path);
      free(redirected_path);
    }
  }
}
