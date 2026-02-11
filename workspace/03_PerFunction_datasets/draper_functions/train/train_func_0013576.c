allocate_basic_variable (struct iv_to_split *ivts)
{
  rtx expr = *get_ivts_expr (single_set (ivts->insn), ivts);

  ivts->base_var = gen_reg_rtx (GET_MODE (expr));
}
