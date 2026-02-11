loopcxt_get_sysfs(struct loopdev_cxt *lc)
{
	if (!lc || !*lc->device || (lc->flags & LOOPDEV_FL_NOSYSFS))
		return NULL;

	if (!lc->sysfs.devno) {
		dev_t devno = sysfs_devname_to_devno(lc->device, NULL);
		if (!devno)
			return NULL;

		if (sysfs_init(&lc->sysfs, devno, NULL))
			return NULL;
	}
	return &lc->sysfs;
}
