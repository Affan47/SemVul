df_chain_create_bb (unsigned int bb_index)
{
  basic_block bb = BASIC_BLOCK (bb_index);
  struct df_rd_bb_info *bb_info = df_rd_get_bb_info (bb_index);
  rtx insn;
  bitmap_head cpy;

  bitmap_initialize (&cpy, &bitmap_default_obstack);
  bitmap_copy (&cpy, &bb_info->in);
  bitmap_set_bit (df_chain->out_of_date_transfer_functions, bb_index);


#ifdef EH_USES


  if (!(df->changeable_flags & DF_NO_HARD_REGS))
    df_chain_create_bb_process_use (&cpy,
				    df_get_artificial_uses (bb->index),
				    DF_REF_AT_TOP);
#endif

  df_rd_simulate_artificial_defs_at_top (bb, &cpy);


  FOR_BB_INSNS (bb, insn)
    if (INSN_P (insn))
      {
        unsigned int uid = INSN_UID (insn);


        df_chain_create_bb_process_use (&cpy, DF_INSN_UID_USES (uid), 0);
        if (df->changeable_flags & DF_EQ_NOTES)
	  df_chain_create_bb_process_use (&cpy, DF_INSN_UID_EQ_USES (uid), 0);


        df_rd_simulate_one_insn (bb, insn, &cpy);
      }


  if (!(df->changeable_flags & DF_NO_HARD_REGS))
    df_chain_create_bb_process_use (&cpy,
				    df_get_artificial_uses (bb->index),
				    0);

  bitmap_clear (&cpy);
}
