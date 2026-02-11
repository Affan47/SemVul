analyze_iv_to_split_insn (rtx insn)
{
  rtx set, dest;
  struct rtx_iv iv;
  struct iv_to_split *ivts;
  bool ok;


  set = single_set (insn);
  if (!set)
    return NULL;

  dest = SET_DEST (set);
  if (!REG_P (dest))
    return NULL;

  if (!biv_p (insn, dest))
    return NULL;

  ok = iv_analyze_result (insn, dest, &iv);


  if (! ok)
    return NULL;

  if (iv.step == const0_rtx
      || iv.mode != iv.extend_mode)
    return NULL;


  ivts = XNEW (struct iv_to_split);
  ivts->insn = insn;
  ivts->orig_var = dest;
  ivts->base_var = NULL_RTX;
  ivts->step = iv.step;
  ivts->next = NULL;
  ivts->n_loc = 1;
  ivts->loc[0] = 1;

  return ivts;
}
