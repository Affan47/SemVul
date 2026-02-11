mark_reg_clobber (rtx reg, const_rtx setter, void *data)
{
  if (GET_CODE (setter) == CLOBBER)
    mark_reg_store (reg, setter, data);
}
