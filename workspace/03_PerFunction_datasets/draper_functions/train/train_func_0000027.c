restore_action_replay (uae_u8 *src)
{
	uae_u32 crc32;
	TCHAR *s;

	action_replay_unload (1);
	restore_u8 ();
	armodel = restore_u8 ();
	if (!armodel)
		return src;
	crc32 = restore_u32 ();
	s = restore_string ();
	_tcsncpy (changed_prefs.cartfile, s, 255);
	_tcscpy (currprefs.cartfile, changed_prefs.cartfile);
	xfree (s);
	action_replay_load ();
	if (restore_u32 () != arrom_size)
		return src;
	if (restore_u32 () != arram_size)
		return src;
	if (armemory_ram)
		memcpy (armemory_ram, src, arram_size);
	src += arram_size;
	restore_u32 ();
	memcpy (ar_custom, src, sizeof ar_custom);
	src += sizeof ar_custom;
	restore_u32 ();
	src += sizeof ar_ciaa;
	restore_u32 ();
	src += sizeof ar_ciab;
	action_replay_flag = ACTION_REPLAY_IDLE;
	if (is_ar_pc_in_rom ())
		action_replay_flag = ACTION_REPLAY_ACTIVE;
	return src;
}
