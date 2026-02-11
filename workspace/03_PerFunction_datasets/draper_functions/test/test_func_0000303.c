update(FStream & in, ParmString fn) {
  typedef PosibErr<void> Ret;
  {
    Ret pe = merge(in, fn);
    if (pe.has_err() && compatibility_file_name.empty()) return pe;
  } {
    Ret pe = update_file_date_info(in);
    if (pe.has_err() && compatibility_file_name.empty()) return pe;
  }
  return no_err;
}
