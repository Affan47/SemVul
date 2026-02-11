io_stdfile(lua_State *L, ptrdiff_t id)
{
  IOFileUD *iof = IOSTDF_IOF(L, id);
  if (iof->fp == NULL)
    lj_err_caller(L, LJ_ERR_IOSTDCL);
  return iof->fp;
}
