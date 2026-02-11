cfc_set_check_fn(CplFileConf *cfc, CplCheckFn *chk_fn, void *chk_data)
{
#ifndef WITHOUT_FILE_SYSTEM
  if(cfc) {
    cfc->chk_fn = chk_fn;
    cfc->chk_data = chk_data;
  };
#endif
}
