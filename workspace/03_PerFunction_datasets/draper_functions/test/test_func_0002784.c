CDE_begin_standard_fileop(struct tcb* tcp, const char* syscall_name) {
  char* filename = strcpy_from_child(tcp, tcp->u_arg[0]);

  if (CDE_verbose_mode) {
    printf("[%d] BEGIN %s '%s'\n", tcp->pid, syscall_name, filename);
  }

  if (CDE_exec_mode) {
    if (filename) {
      modify_syscall_single_arg(tcp, 1, filename);
    }
  }
  else {


    if (filename) {
      copy_file_into_cde_root(filename, tcp->current_dir);
    }
  }

  free(filename);
}
