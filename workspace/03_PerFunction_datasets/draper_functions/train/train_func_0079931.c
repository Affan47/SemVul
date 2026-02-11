def_has_ccmode_p (rtx insn)
{
  df_ref *def;

  for (def = DF_INSN_DEFS (insn); *def; def++)
    {
      enum machine_mode mode = GET_MODE (DF_REF_REG (*def));

      if (GET_MODE_CLASS (mode) == MODE_CC)
	return true;
    }

  return false;
}
