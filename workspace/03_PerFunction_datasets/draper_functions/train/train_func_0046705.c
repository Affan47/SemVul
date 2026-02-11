CDE_begin_file_symlinkat(struct tcb* tcp) {
  if (CDE_verbose_mode) {
    printf("[%d] BEGIN symlinkat\n", tcp->pid);
  }

  char* newpath = strcpy_from_child(tcp, tcp->u_arg[2]);

  if (!IS_ABSPATH(newpath) && tcp->u_arg[1] != AT_FDCWD) {
    fprintf(stderr, "CDE WARNING: symlinkat '%s' is a relative path and dirfd != AT_FDCWD\n", newpath);
    free(newpath);
    return;
  }

  if (CDE_exec_mode) {
    modify_syscall_first_and_third_args(tcp);
  }
  else {
    char* oldname = strcpy_from_child(tcp, tcp->u_arg[0]);
    char* newpath_redirected = redirect_filename_into_cderoot(newpath, tcp->current_dir, tcp);
    symlink(oldname, newpath_redirected);

    free(oldname);
    free(newpath_redirected);
  }

  free(newpath);
}
