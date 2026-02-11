cifs_clear_stats(struct cifs_tcon *tcon)
{
#ifdef CONFIG_CIFS_STATS
	atomic_set(&tcon->stats.cifs_stats.num_writes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_reads, 0);
	atomic_set(&tcon->stats.cifs_stats.num_flushes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_oplock_brks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_opens, 0);
	atomic_set(&tcon->stats.cifs_stats.num_posixopens, 0);
	atomic_set(&tcon->stats.cifs_stats.num_posixmkdirs, 0);
	atomic_set(&tcon->stats.cifs_stats.num_closes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_deletes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_mkdirs, 0);
	atomic_set(&tcon->stats.cifs_stats.num_rmdirs, 0);
	atomic_set(&tcon->stats.cifs_stats.num_renames, 0);
	atomic_set(&tcon->stats.cifs_stats.num_t2renames, 0);
	atomic_set(&tcon->stats.cifs_stats.num_ffirst, 0);
	atomic_set(&tcon->stats.cifs_stats.num_fnext, 0);
	atomic_set(&tcon->stats.cifs_stats.num_fclose, 0);
	atomic_set(&tcon->stats.cifs_stats.num_hardlinks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_symlinks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_locks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_acl_get, 0);
	atomic_set(&tcon->stats.cifs_stats.num_acl_set, 0);
#endif
}
