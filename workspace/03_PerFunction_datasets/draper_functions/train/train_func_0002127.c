Term_Math_Loading(WamWord l_word, WamWord r_word)
{
  WamWord word, tag_mask;
  WamWord *adr, *fdv_adr;

  if (delay_sp != delay_cstr_stack)
    {
#ifdef DEBUG
      DBGPRINTF("\nnon Linear part\n");
#endif
      if (!Load_Delay_Cstr_Part())
	return FALSE;
    }

  while (--vars_sp >= vars_tbl)
    {
      DEREF(*vars_sp, word, tag_mask);
      if (tag_mask == TAG_REF_MASK && word != l_word && word != r_word)
	{
	  adr = UnTag_REF(word);
	  fdv_adr = Fd_New_Variable();
	  Bind_UV(adr, Tag_REF(fdv_adr));
	}
    }

  return TRUE;
}
