gt_pch_pa_regno_reg_rtx (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no) && ((void *)regno_reg_rtx == this_obj); i0++) {
      if ((void *)(regno_reg_rtx) == this_obj)
        op (&(regno_reg_rtx[i0]), cookie);
    }
    if ((void *)(&regno_reg_rtx) == this_obj)
      op (&(regno_reg_rtx), cookie);
  }
}
