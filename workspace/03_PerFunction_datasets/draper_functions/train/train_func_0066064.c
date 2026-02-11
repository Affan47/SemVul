recff_table_getn(jit_State *J, RecordFFData *rd)
{
  if (tref_istab(J->base[0]))
    J->base[0] = lj_ir_call(J, IRCALL_lj_tab_len, J->base[0]);

  UNUSED(rd);
}
