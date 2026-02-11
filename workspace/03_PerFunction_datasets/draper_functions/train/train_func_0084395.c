dump_record(dbcallback_i& cb, TABLE *const table,
  const prep_stmt& pst)
{
  char rwpstr_buf[64];
  String rwpstr(rwpstr_buf, sizeof(rwpstr_buf), &my_charset_bin);
  const prep_stmt::fields_type& rf = pst.get_ret_fields();
  const size_t n = rf.size();
  for (size_t i = 0; i < n; ++i) {
    uint32_t fn = rf[i];
    Field *const fld = table->field[fn];
    if (fld->is_null()) {

      fprintf(stderr, "NULL");
    } else {
      fld->val_str(&rwpstr, &rwpstr);
      const std::string s(rwpstr.ptr(), rwpstr.length());
      fprintf(stderr, "[%s]", s.c_str());
    }
  }
  fprintf(stderr, "\n");
}
