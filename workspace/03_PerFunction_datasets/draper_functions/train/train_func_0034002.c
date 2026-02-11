load_killed_in_block_p (basic_block bb, int uid_limit, rtx x, int avail_p)
{
  rtx list_entry = modify_mem_list[bb->index];
  while (list_entry)
    {
      rtx setter;

      if ((avail_p
	   && INSN_CUID (XEXP (list_entry, 0)) < uid_limit)
	  || (! avail_p
	      && INSN_CUID (XEXP (list_entry, 0)) > uid_limit))
	{
	  list_entry = XEXP (list_entry, 1);
	  continue;
	}

      setter = XEXP (list_entry, 0);


      if (GET_CODE (setter) == CALL_INSN)
	return 1;


      gcse_mem_operand = x;
      gcse_mems_conflict_p = 0;
      note_stores (PATTERN (setter), mems_conflict_for_gcse_p, NULL);
      if (gcse_mems_conflict_p)
	return 1;
      list_entry = XEXP (list_entry, 1);
    }
  return 0;
}
