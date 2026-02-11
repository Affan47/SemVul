db_get_dbname (DB* db, int errorp) {
  const char *fname, *dbname;
  int status;
  begin_system_call();
  status = db->get_dbname(db,&fname,&dbname);
  end_system_call();
  if (status) {
    if (errorp) error_bdb(status,"db->get_dbname");
    error_message_reset();
    value1 = value2 = NIL;
  } else {
    pushSTACK(asciz_to_string0(fname,GLO(pathname_encoding)));
    value2 = safe_to_string(dbname);
    value1 = popSTACK();
  }
}
