df_ref_dump (df_ref ref, FILE *file)
{
  fprintf (file, "%c%d(%d)",
	   DF_REF_REG_DEF_P (ref)
	   ? 'd'
	   : (DF_REF_FLAGS (ref) & DF_REF_IN_NOTE) ? 'e' : 'u',
	   DF_REF_ID (ref),
	   DF_REF_REGNO (ref));
}
