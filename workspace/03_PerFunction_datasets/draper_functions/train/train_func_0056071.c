fsm_vacuum_page(Relation rel, FSMAddress addr, bool *eof_p)
{
	Buffer		buf;
	Page		page;
	uint8		max_avail;


	buf = fsm_readbuf(rel, addr, false);
	if (!BufferIsValid(buf))
	{
		*eof_p = true;
		return 0;
	}
	else
		*eof_p = false;

	page = BufferGetPage(buf);


	if (addr.level > FSM_BOTTOM_LEVEL)
	{
		int			slot;
		bool		eof = false;

		for (slot = 0; slot < SlotsPerFSMPage; slot++)
		{
			int			child_avail;


			if (!eof)
				child_avail = fsm_vacuum_page(rel, fsm_get_child(addr, slot), &eof);
			else
				child_avail = 0;


			if (fsm_get_avail(page, slot) != child_avail)
			{
				LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
				fsm_set_avail(BufferGetPage(buf), slot, child_avail);
				MarkBufferDirty(buf);
				LockBuffer(buf, BUFFER_LOCK_UNLOCK);
			}
		}
	}

	max_avail = fsm_get_max_avail(BufferGetPage(buf));


	((FSMPage) PageGetContents(page))->fp_next_slot = 0;

	ReleaseBuffer(buf);

	return max_avail;
}
