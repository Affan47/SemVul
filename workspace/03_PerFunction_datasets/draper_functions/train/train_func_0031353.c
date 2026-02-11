df_chain_create_bb_process_use (bitmap local_rd,
				df_ref *use_rec,
				int top_flag)
{
  bitmap_iterator bi;
  unsigned int def_index;

  while (*use_rec)
    {
      df_ref use = *use_rec;
      unsigned int uregno = DF_REF_REGNO (use);
      if ((!(df->changeable_flags & DF_NO_HARD_REGS))
	  || (uregno >= FIRST_PSEUDO_REGISTER))
	{

	  int count = DF_DEFS_COUNT (uregno);
	  if (count)
	    {
	      if (top_flag == (DF_REF_FLAGS (use) & DF_REF_AT_TOP))
		{
		  unsigned int first_index = DF_DEFS_BEGIN (uregno);
		  unsigned int last_index = first_index + count - 1;

		  EXECUTE_IF_SET_IN_BITMAP (local_rd, first_index, def_index, bi)
		    {
		      df_ref def;
		      if (def_index > last_index)
			break;

		      def = DF_DEFS_GET (def_index);
		      if (df_chain_problem_p (DF_DU_CHAIN))
			df_chain_create (def, use);
		      if (df_chain_problem_p (DF_UD_CHAIN))
			df_chain_create (use, def);
		    }
		}
	    }
	}

      use_rec++;
    }
}
