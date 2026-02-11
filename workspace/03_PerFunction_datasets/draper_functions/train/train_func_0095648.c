trap_filter(rwlock_t *lock, entry_t **entry, peer_cfg_t **peer_cfg,
						void *none, child_sa_t **child_sa)
{
	if (!(*entry)->child_sa)
	{
		return FALSE;
	}
	if (peer_cfg)
	{
		*peer_cfg = (*entry)->peer_cfg;
	}
	if (child_sa)
	{
		*child_sa = (*entry)->child_sa;
	}
	return TRUE;
}
