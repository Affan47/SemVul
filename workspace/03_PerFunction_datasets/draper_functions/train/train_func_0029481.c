df_bb_single_def_use_insn_find (df, bb, insn, reg)
     struct df * df;
     basic_block bb;
     rtx insn;
     rtx reg;
{
  struct ref *def;
  struct ref *use;
  struct df_link *du_link;

  def = df_bb_insn_regno_first_def_find (df, bb, insn, REGNO (reg));

  if (! def)
    abort ();

  du_link = DF_REF_CHAIN (def);

  if (! du_link)
    return NULL_RTX;

  use = du_link->ref;


  if (! use)
    return NULL_RTX;


  if (du_link->next)
    return NULL_RTX;

  return DF_REF_INSN (use);
}
