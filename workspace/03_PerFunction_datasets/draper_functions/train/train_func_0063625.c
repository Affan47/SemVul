gt_ggc_ma_regno_reg_rtx (ATTRIBUTE_UNUSED void *x_p)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no); i0++) {
      gt_ggc_m_7rtx_def (regno_reg_rtx[i0]);
    }
    ggc_mark (regno_reg_rtx);
  }
}
