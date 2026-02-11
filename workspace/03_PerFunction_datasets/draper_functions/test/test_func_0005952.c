dbe_get_cache (DB_ENV* dbe, int errorp) {
  u_int32_t gbytes, bytes;
  int ncache, status;
  begin_system_call();
  status = dbe->get_cachesize(dbe,&gbytes,&bytes,&ncache);
  end_system_call();
  if (status) {
    if (errorp) error_bdb(status,"dbe->get_cachesize");
    error_message_reset();
    value1 = value2 = NIL;
  } else cache2lisp (gbytes, bytes, ncache);
}
