gt_ggc_mx_machine_function (void *x_p)
{
  struct machine_function * const x = (struct machine_function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).eh_epilogue_sp_ofs);
      gt_ggc_m_7rtx_def ((*x).pic_reg);
      {
        size_t i0;
        size_t l0 = (size_t)(14);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_7rtx_def ((*x).call_via[i0]);
        }
      }
      gt_ggc_m_7rtx_def ((*x).thumb1_cc_insn);
      gt_ggc_m_7rtx_def ((*x).thumb1_cc_op0);
      gt_ggc_m_7rtx_def ((*x).thumb1_cc_op1);
    }
}
