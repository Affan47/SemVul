au_fhsm_init(struct au_sbinfo *sbinfo)
{
	struct au_fhsm *fhsm;

	fhsm = &sbinfo->si_fhsm;
	spin_lock_init(&fhsm->fhsm_spin);
	init_waitqueue_head(&fhsm->fhsm_wqh);
	atomic_set(&fhsm->fhsm_readable, 0);
	fhsm->fhsm_expire
		= msecs_to_jiffies(AUFS_FHSM_CACHE_DEF_SEC * MSEC_PER_SEC);
	fhsm->fhsm_bottom = -1;
}
