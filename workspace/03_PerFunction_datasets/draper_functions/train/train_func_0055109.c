lvmcache_vgname_is_locked(const char *vgname)
{
	if (!_lock_hash)
		return 0;

	return dm_hash_lookup(_lock_hash, is_orphan_vg(vgname) ? VG_ORPHANS : vgname) ? 1 : 0;
}
