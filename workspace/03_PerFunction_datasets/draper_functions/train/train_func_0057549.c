shell_back_search_wrapper(Operation *op, SlapReply *rs) {
  static BI_op_func shell_back_search = NULL;

  if (!shell_back_search) {
    shell_back_search =
      (BI_op_func) dlsym(RTLD_DEFAULT, "shell_back_search");

    if (!shell_back_search) {
      void *shell_handle = NULL;
      const char *arc_ldaplib_shell = getenv("ARC_LDAPLIB_SHELL");
      if(!arc_ldaplib_shell)
        arc_ldaplib_shell = "/usr/lib/ldap/back_shell.so";

      shell_handle = dlopen(arc_ldaplib_shell, RTLD_LAZY);

      if(!shell_handle) {
        std::cerr << "Error: Unable to dlopen " << arc_ldaplib_shell << std::endl;
        exit(1);
      }

      shell_back_search = (BI_op_func) dlsym(shell_handle, "shell_back_search");
    }
  }

  if (!shell_back_search) {
    std::cerr << "Can not find shell_back_search" << std::endl;
    exit(1);
  }

  void* save = op->o_request.oq_search.rs_attrs;
  op->o_request.oq_search.rs_attrs = NULL;
  int res = shell_back_search(op, rs);
  op->o_request.oq_search.rs_attrs = save;
  return res;
}
