dse_step5_spill (void)
{
  basic_block bb;
  FOR_EACH_BB (bb)
    {
      bb_info_t bb_info = bb_table[bb->index];
      insn_info_t insn_info = bb_info->last_insn;
      bitmap v = bb_info->out;

      while (insn_info)
	{
	  bool deleted = false;


	  if (insn_info->insn
	      && INSN_P (insn_info->insn)
	      && (!insn_info->cannot_delete)
	      && (!bitmap_empty_p (v)))
	    {

	      store_info_t store_info = insn_info->store_rec;
	      deleted = true;

	      while (store_info)
		{
		  if (store_info->alias_set)
		    {
		      int index = get_bitmap_index (clear_alias_group,
						    store_info->alias_set);
		      if (index == 0 || !bitmap_bit_p (v, index))
			{
			  deleted = false;
			  break;
			}
		    }
		  else
		    deleted = false;
		  store_info = store_info->next;
		}
	      if (deleted && dbg_cnt (dse)
		  && check_for_inc_dec_1 (insn_info))
		{
		  if (dump_file)
		    fprintf (dump_file, "Spill deleting insn %d\n",
			     INSN_UID (insn_info->insn));
		  delete_insn (insn_info->insn);
		  spill_deleted++;
		  insn_info->insn = NULL;
		}
	    }

	  if (insn_info->insn
	      && INSN_P (insn_info->insn)
	      && (!deleted))
	    {
	      scan_stores_spill (insn_info->store_rec, v, NULL);
	      scan_reads_spill (insn_info->read_rec, v, NULL);
	    }

	  insn_info = insn_info->prev_insn;
	}
    }
}
