recurse_aino (UnitInfo *ui, a_inode *a, int cnt, uae_u8 **dstp)
{
	uae_u8 *dst = NULL;
	int dirty = 0;
	a_inode *a2 = a;

	if (dstp)
		dst = *dstp;
	while (a) {

		if (a->elock || a->shlock || a->uniq == 0) {
			if (dst) {
				TCHAR *fn = NULL;
				write_log (_T("uniq=%d %lld s=%d e=%d d=%d '%s' '%s'\n"), a->uniq, a->uniq_external, a->shlock, a->elock, a->dir, a->aname, a->nname);
				if (a->aname) {
					fn = getfullaname (a);
					write_log (_T("->'%s'\n"), fn);
				}
				save_u64 (a->uniq);
				save_u32 (a->locked_children);
				save_u32 (a->exnext_count);
				save_u32 (a->shlock);
				save_u32 ((a->elock ? 1 : 0) | (a->dir ? 2 : 0) | 4);
				save_u64 (a->uniq_external);
				save_string (fn);
				xfree(fn);
			}
			cnt++;
		}
		if (a->dirty)
			dirty = 1;
		if (a->child)
			cnt = recurse_aino (ui, a->child, cnt, &dst);
		a = a->sibling;
	}
	if (dirty && a2->parent)
		fsdb_dir_writeback (a2->parent);
	if (dst)
		*dstp = dst;
	return cnt;
}
