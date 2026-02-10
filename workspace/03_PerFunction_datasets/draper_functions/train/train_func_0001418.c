df_bb_du_chain_create (df, bb, ru)
     struct df *df;
     basic_block bb;
     bitmap ru;
{
  struct bb_info *bb_info = DF_BB_INFO (df, bb);
  rtx insn;

  bitmap_copy (ru, bb_info->ru_out);


  for (insn = bb->end; insn && insn != PREV_INSN (bb->head);
       insn = PREV_INSN (insn))
    {
      struct df_link *def_link;
      struct df_link *use_link;
      unsigned int uid = INSN_UID (insn);

      if (! INSN_P (insn))
	continue;


      for (def_link = df->insns[uid].defs; def_link; def_link = def_link->next)
	{
	  struct ref *def = def_link->ref;
	  unsigned int dregno = DF_REF_REGNO (def);

	  DF_REF_CHAIN (def) = 0;


	  for (use_link = df->regs[dregno].uses; use_link;
	       use_link = use_link->next)
	    {
	      struct ref *use = use_link->ref;

	      if (bitmap_bit_p (ru, DF_REF_ID (use)))
		{
		  DF_REF_CHAIN (def)
		    = df_link_create (use, DF_REF_CHAIN (def));

		  bitmap_clear_bit (ru, DF_REF_ID (use));
		}
	    }
	}


      for (use_link = df->insns[uid].uses; use_link; use_link = use_link->next)
	{
	  struct ref *use = use_link->ref;
	  bitmap_set_bit (ru, DF_REF_ID (use));
	}
    }
}
