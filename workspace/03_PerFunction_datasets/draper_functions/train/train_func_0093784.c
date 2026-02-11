vt_expand_1pvar (variable var, htab_t vars)
{
  struct expand_loc_callback_data data;
  rtx loc;

  gcc_checking_assert (var->onepart && var->n_var_parts == 1);

  if (!dv_changed_p (var->dv))
    return var->var_part[0].cur_loc;

  INIT_ELCD (data, vars);

  loc = vt_expand_var_loc_chain (var, scratch_regs, &data, NULL);

  gcc_checking_assert (data.expanding.is_empty ());

  FINI_ELCD (data, loc);

  return loc;
}
