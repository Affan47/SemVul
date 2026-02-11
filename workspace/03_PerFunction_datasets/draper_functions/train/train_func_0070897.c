df_chain_bottom_dump (basic_block bb, FILE *file)
{
  if (df_chain_problem_p (DF_UD_CHAIN))
    {
      rtx insn;
      df_ref *use_rec = df_get_artificial_uses (bb->index);

      if (*use_rec)
	{
	  fprintf (file, ";;  UD chains for artificial uses\n");
	  while (*use_rec)
	    {
	      df_ref use = *use_rec;
	      fprintf (file, ";;   reg %d ", DF_REF_REGNO (use));
	      df_chain_dump (DF_REF_CHAIN (use), file);
	      fprintf (file, "\n");
	      use_rec++;
	    }
	}

      FOR_BB_INSNS (bb, insn)
	{
	  if (INSN_P (insn))
	    {
	      struct df_insn_info *insn_info = DF_INSN_INFO_GET (insn);
	      df_ref *eq_use_rec = DF_INSN_INFO_EQ_USES (insn_info);
	      use_rec = DF_INSN_INFO_USES (insn_info);
	      if (*use_rec || *eq_use_rec)
		{
		  fprintf (file, ";;   UD chains for insn luid %d uid %d\n",
			   DF_INSN_INFO_LUID (insn_info), INSN_UID (insn));

		  while (*use_rec)
		    {
		      df_ref use = *use_rec;
		      fprintf (file, ";;      reg %d ", DF_REF_REGNO (use));
		      if (DF_REF_FLAGS (use) & DF_REF_READ_WRITE)
			fprintf (file, "read/write ");
		      df_chain_dump (DF_REF_CHAIN (use), file);
		      fprintf (file, "\n");
		      use_rec++;
		    }
		  while (*eq_use_rec)
		    {
		      df_ref use = *eq_use_rec;
		      fprintf (file, ";;   eq_note reg %d ", DF_REF_REGNO (use));
		      df_chain_dump (DF_REF_CHAIN (use), file);
		      fprintf (file, "\n");
		      eq_use_rec++;
		    }
		}
	    }
	}
    }
}
