df_regno_bb (struct df *df, unsigned int regno)
{
  struct df_link *defs = df->regs[regno].defs;
  struct df_link *uses = df->regs[regno].uses;
  struct ref *def = defs ? defs->ref : 0;
  struct ref *use = uses ? uses->ref : 0;
  basic_block bb_def = def ? DF_REF_BB (def) : 0;
  basic_block bb_use = use ? DF_REF_BB (use) : 0;


  return bb_def == bb_use ? bb_def : 0;
}
