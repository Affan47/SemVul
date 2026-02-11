action_examine_next (Unit *unit, dpacket packet)
{
	uaecptr lock = GET_PCK_ARG1 (packet) << 2;
	uaecptr info = GET_PCK_ARG2 (packet) << 2;
	a_inode *aino = 0;
	ExamineKey *ek;
	uae_u32 uniq;

	TRACE((_T("ACTION_EXAMINE_NEXT(0x%lx,0x%lx)\n"), lock, info));
	gui_flicker_led (UNIT_LED(unit), unit->unit, 1);
	DUMPLOCK(unit, lock);

	if (lock != 0)
		aino = lookup_aino (unit, get_long (lock + 4));
	if (aino == 0)
		aino = &unit->rootnode;
	for(;;) {
		uniq = get_long (info);
		if (uniq == 0) {
			write_log (_T("ExNext called for a file! (Houston?)\n"));
			goto no_more_entries;
		} else if (uniq == 0xFFFFFFFE)
			goto no_more_entries;
		else if (uniq == 0xFFFFFFFF) {
			TRACE((_T("Creating new ExKey\n")));
			ek = new_exkey (unit, aino);
			if (ek) {
				if (aino->exnext_count++ == 0)
#ifdef FSUAE
				{
				    g_packet_delay = 320;
#endif
					populate_directory (unit, aino);
#ifdef FSUAE
				}
#endif
				ek->curr_file = aino->child;
				TRACE((_T("Initial curr_file: %p %s\n"), ek->curr_file,
					ek->curr_file ? ek->curr_file->aname : _T("NULL")));
			}
		} else {
			TRACE((_T("Looking up ExKey\n")));
			ek = lookup_exkey (unit, get_long (info));
		}
		if (ek == 0) {
			write_log (_T("Couldn't find a matching ExKey. Prepare for trouble.\n"));
			goto no_more_entries;
		}
		put_long (info, ek->uniq);
		if (!ek->curr_file || ek->curr_file->mountcount == unit->mountcount)
			break;
		ek->curr_file = ek->curr_file->sibling;
		if (!ek->curr_file)
			goto no_more_entries;
	}
	do_examine (unit, packet, ek, info);
	return;

no_more_entries:
	PUT_PCK_RES1 (packet, DOS_FALSE);
	PUT_PCK_RES2 (packet, ERROR_NO_MORE_ENTRIES);
}
