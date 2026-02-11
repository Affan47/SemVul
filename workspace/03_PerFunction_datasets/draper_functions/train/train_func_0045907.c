dbe_get_home_dir (DB_ENV *dbe, int errorp) {
  const char *home;
  int status;
  begin_system_call();
  status = dbe->get_home(dbe,&home);
  end_system_call();
  if (status) {
    if (errorp) error_bdb(status,"dbe->get_home");
    error_message_reset(); return T;
  }
  if (home == NULL) return NIL;
  return asciz_to_string(home,GLO(pathname_encoding));
}
