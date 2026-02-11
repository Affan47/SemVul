pnfs_register_layoutdriver(struct pnfs_layoutdriver_type *ld_type)
{
	int status = -EINVAL;
	struct pnfs_layoutdriver_type *tmp;

	if (ld_type->id == 0) {
		printk(KERN_ERR "NFS: %s id 0 is reserved\n", __func__);
		return status;
	}
	if (!ld_type->alloc_lseg || !ld_type->free_lseg) {
		printk(KERN_ERR "NFS: %s Layout driver must provide "
		       "alloc_lseg and free_lseg.\n", __func__);
		return status;
	}

	spin_lock(&pnfs_spinlock);
	tmp = find_pnfs_driver_locked(ld_type->id);
	if (!tmp) {
		list_add(&ld_type->pnfs_tblid, &pnfs_modules_tbl);
		status = 0;
		dprintk("%s Registering id:%u name:%s\n", __func__, ld_type->id,
			ld_type->name);
	} else {
		printk(KERN_ERR "NFS: %s Module with id %d already loaded!\n",
			__func__, ld_type->id);
	}
	spin_unlock(&pnfs_spinlock);

	return status;
}
