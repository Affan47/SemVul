dead_debug_reset_uses (struct dead_debug_local *debug,
		       struct dead_debug_use *head)
{
  bool got_head = (debug->head == head);
  bitmap rescan;
  struct dead_debug_use **tailp = &debug->head;
  struct dead_debug_use *cur;
  bitmap_iterator bi;
  unsigned int uid;

  if (got_head)
    rescan = NULL;
  else
    rescan = BITMAP_ALLOC (NULL);

  while (head)
    {
      struct dead_debug_use *next = head->next;
      rtx insn;

      insn = DF_REF_INSN (head->use);
      if (!next || DF_REF_INSN (next->use) != insn)
	{
	  INSN_VAR_LOCATION_LOC (insn) = gen_rtx_UNKNOWN_VAR_LOC ();
	  if (got_head)
	    df_insn_rescan_debug_internal (insn);
	  else
	    bitmap_set_bit (rescan, INSN_UID (insn));
	  if (debug->to_rescan)
	    bitmap_clear_bit (debug->to_rescan, INSN_UID (insn));
	}
      XDELETE (head);
      head = next;
    }

  if (got_head)
    {
      debug->head = NULL;
      return;
    }

  while ((cur = *tailp))
    if (bitmap_bit_p (rescan, INSN_UID (DF_REF_INSN (cur->use))))
      {
	*tailp = cur->next;
	XDELETE (cur);
      }
    else
      tailp = &cur->next;

  EXECUTE_IF_SET_IN_BITMAP (rescan, 0, uid, bi)
    {
      struct df_insn_info *insn_info = DF_INSN_UID_SAFE_GET (uid);
      if (insn_info)
	df_insn_rescan_debug_internal (insn_info->insn);
    }

  BITMAP_FREE (rescan);
}
