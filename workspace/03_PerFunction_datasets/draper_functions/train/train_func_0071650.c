reset_errpfx (DB_ENV *dbe) {
  close_errpfx(dbe);
  if (nullp(STACK_0)) {
    begin_system_call(); dbe->set_errpfx(dbe,NULL); end_system_call();
  } else
    with_string_0(check_string(STACK_0),GLO(misc_encoding), prefix, {
        char *errpfx = (char*)clisp_malloc(prefix_bytelen+1);
        begin_system_call();
        strcpy(errpfx,prefix);
        dbe->set_errpfx(dbe,errpfx);
        end_system_call();
      });
}
