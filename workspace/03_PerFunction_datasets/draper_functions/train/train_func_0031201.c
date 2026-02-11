my_fopen (object path) {
  FILE *ret;
  with_string_0(path=physical_namestring(path),GLO(pathname_encoding),pathz,{
      begin_blocking_system_call();
      ret = fopen(pathz,"w");
      if (ret == NULL) { end_blocking_system_call(); OS_file_error(path); }
      time_stamp(ret,"opened");
      end_blocking_system_call();
    });
  return ret;
}
