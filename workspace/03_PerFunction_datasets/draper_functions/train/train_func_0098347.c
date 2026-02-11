df_simulate_find_uses (rtx insn, bitmap uses)
{
  df_ref *rec;
  unsigned int uid = INSN_UID (insn);

  for (rec = DF_INSN_UID_DEFS (uid); *rec; rec++)
    {
      df_ref def = *rec;
      if (DF_REF_FLAGS (def) & (DF_REF_PARTIAL | DF_REF_CONDITIONAL))
	bitmap_set_bit (uses, DF_REF_REGNO (def));
    }
  for (rec = DF_INSN_UID_USES (uid); *rec; rec++)
    {
      df_ref use = *rec;
      bitmap_set_bit (uses, DF_REF_REGNO (use));
    }
}
