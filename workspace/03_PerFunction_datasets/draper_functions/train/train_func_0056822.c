read_state_files_list (void)
{
  struct state_token_st *t0 = peek_state_token (0);
  struct state_token_st *t1 = peek_state_token (1);
  struct state_token_st *t2 = peek_state_token (2);

  if (state_token_kind (t0) == STOK_LEFTPAR
      && state_token_is_name (t1, "!fileslist")
      && state_token_kind (t2) == STOK_INTEGER)
    {
      int i = 0;
      num_gt_files = t2->stok_un.stok_num;
      next_state_tokens (3);
      t0 = t1 = t2 = NULL;
      gt_files = XCNEWVEC (const input_file *, num_gt_files);
      for (i = 0; i < (int) num_gt_files; i++)
	{
	  bool issrcfile = FALSE;
	  t0 = t1 = t2 = NULL;
	  t0 = peek_state_token (0);
	  t1 = peek_state_token (1);
	  t2 = peek_state_token (2);
	  if (state_token_kind (t0) == STOK_LEFTPAR
	      && (state_token_is_name (t1, "!file")
		  || (issrcfile = state_token_is_name (t1, "!srcfile")))
	      && state_token_kind (t2) == STOK_INTEGER)
	    {
	      lang_bitmap bmap = t2->stok_un.stok_num;
	      next_state_tokens (3);
	      t0 = t1 = t2 = NULL;
	      t0 = peek_state_token (0);
	      t1 = peek_state_token (1);
	      if (state_token_kind (t0) == STOK_STRING
		  && state_token_kind (t1) == STOK_RIGHTPAR)
		{
		  const char *fnam = t0->stok_un.stok_string;

		  input_file *curgt = NULL;
		  if (issrcfile)
		    {
		      static const char dirsepstr[2] =
			{ DIR_SEPARATOR, (char) 0 };
		      char *fullpath = concat (srcdir, dirsepstr, fnam, NULL);
		      curgt = input_file_by_name (fullpath);
		      free (fullpath);
		    }
		  else
		    curgt = input_file_by_name (fnam);
		  set_lang_bitmap (curgt, bmap);
		  gt_files[i] = curgt;
		  next_state_tokens (2);
		}
	      else
		fatal_reading_state (t0,
				     "bad file in !fileslist of state file");
	    }
	  else
	    fatal_reading_state (t0,
				 "expecting file in !fileslist of state file");
	};
      t0 = peek_state_token (0);
      if (state_token_kind (t0) != STOK_RIGHTPAR)
	fatal_reading_state (t0, "missing ) for !fileslist in state file");
      next_state_tokens (1);
    }
  else
    fatal_reading_state (t0, "missing !fileslist in state file");
}
