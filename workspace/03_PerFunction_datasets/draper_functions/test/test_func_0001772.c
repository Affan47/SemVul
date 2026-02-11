save_as(ParmString fn) {
  compatibility_file_name = "";
  set_file_name(fn);
  FStream inout;
  RET_ON_ERR(open_file_writelock(inout, file_name()));
  RET_ON_ERR(save2(inout, file_name()));
  RET_ON_ERR(update_file_date_info(inout));
  return no_err;
}
