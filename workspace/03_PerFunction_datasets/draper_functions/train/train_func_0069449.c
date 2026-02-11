edac_mc_del_mc(struct device *dev)
{
	struct mem_ctl_info *mci;

	edac_dbg(0, "\n");

	mutex_lock(&mem_ctls_mutex);


	mci = find_mci_by_dev(dev);
	if (mci == NULL) {
		mutex_unlock(&mem_ctls_mutex);
		return NULL;
	}

	if (!del_mc_from_global_list(mci))
		edac_mc_owner = NULL;
	mutex_unlock(&mem_ctls_mutex);


	edac_mc_workq_teardown(mci);


	mci->op_state = OP_OFFLINE;


	edac_remove_sysfs_mci_device(mci);

	edac_printk(KERN_INFO, EDAC_MC,
		"Removed device %d for %s %s: DEV %s\n", mci->mc_idx,
		mci->mod_name, mci->ctl_name, edac_dev_name(mci));

	return mci;
}
