hwmgr_fini(struct pp_hwmgr *hwmgr)
{
	if (hwmgr == NULL || hwmgr->ps == NULL)
		return -EINVAL;

	kfree(hwmgr->ps);
	kfree(hwmgr);
	return 0;
}
