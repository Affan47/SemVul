read_state_languages (void)
{
  struct state_token_st *t0 = peek_state_token (0);
  struct state_token_st *t1 = peek_state_token (1);
  struct state_token_st *t2 = peek_state_token (2);
  if (state_token_kind (t0) == STOK_LEFTPAR
      && state_token_is_name (t1, "!languages")
      && state_token_kind (t2) == STOK_INTEGER)
    {
      int i = 0;
      num_lang_dirs = t2->stok_un.stok_num;
      lang_dir_names = XCNEWVEC (const char *, num_lang_dirs);
      next_state_tokens (3);
      t0 = t1 = t2 = NULL;
      for (i = 0; i < (int) num_lang_dirs; i++)
	{
	  t0 = peek_state_token (0);
	  if (state_token_kind (t0) != STOK_NAME)
	    fatal_reading_state (t0, "expecting language name in state file");
	  lang_dir_names[i] = t0->stok_un.stok_ident->stid_name;
	  next_state_tokens (1);
	}
      t0 = peek_state_token (0);
      if (state_token_kind (t0) != STOK_RIGHTPAR)
	fatal_reading_state (t0, "missing ) in languages list of state file");
      next_state_tokens (1);
    }
  else
    fatal_reading_state (t0, "expecting languages list in state file");

}
