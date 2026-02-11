df_simulate_find_noclobber_defs (rtx insn, bitmap defs)
{
  df_ref *def_rec;
  unsigned int uid = INSN_UID (insn);

  for (def_rec = DF_INSN_UID_DEFS (uid); *def_rec; def_rec++)
    {
      df_ref def = *def_rec;
      if (!(DF_REF_FLAGS (def) & (DF_REF_MUST_CLOBBER | DF_REF_MAY_CLOBBER)))
	bitmap_set_bit (defs, DF_REF_REGNO (def));
    }
}
