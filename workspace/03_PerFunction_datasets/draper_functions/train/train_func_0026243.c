restore_filesys_virtual (UnitInfo *ui, uae_u8 *src, int num)
{
	Unit *u = startup_create_unit (ui, num);
	int cnt;

	u->dosbase = restore_u32 ();
	u->volume = restore_u32 ();
	u->port = restore_u32 ();
	u->locklist = restore_u32 ();
	u->dummy_message = restore_u32 ();
	u->cmds_sent = restore_u64 ();
	u->cmds_complete = restore_u64 ();
	u->cmds_acked = restore_u64 ();
	u->next_exkey = restore_u32 ();
	u->total_locked_ainos = restore_u32 ();
	u->volflags = ui->volflags;

	cnt = restore_u32 ();
	write_log (_T("FS: restoring %d locks\n"), cnt);
	while (cnt-- > 0)
		src = restore_aino (ui, u, src);

	cnt = restore_u32 ();
	write_log (_T("FS: restoring %d open files\n"), cnt);
	while (cnt-- > 0)
		src = restore_key (ui, u, src);

	cnt = restore_u32 ();
	write_log (_T("FS: restoring %d notifications\n"), cnt);
	while (cnt-- > 0)
		src = restore_notify (ui, u, src);

	cnt = restore_u32 ();
	write_log (_T("FS: restoring %d exkeys\n"), cnt);
	while (cnt-- > 0)
		src = restore_exkey (ui, u, src);

	return src;
}
