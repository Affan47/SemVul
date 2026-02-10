get_boot_info(struct boot_context *context, char *rootdir,
			 char *subsys)
{
	char initiator_dir[FILENAMESZ];
	int rc = ENODEV;
	int nic_idx = -1, tgt_idx = -1;

	memset(&initiator_dir, 0 , FILENAMESZ);
	snprintf(initiator_dir, FILENAMESZ, "%sinitiator", rootdir);

	nic_cnt = 0;
	tgt_cnt = 0;
	if (file_exist(initiator_dir)) {

		rc = nftw(rootdir, find_sysfs_dirs, 20, 1);


		rc = find_boot_flag(subsys, nic_list, nic_cnt, &nic_idx);
		if (rc)
			goto free;

		rc = find_boot_flag(subsys, target_list, tgt_cnt, &tgt_idx);
		if (rc)
			goto free;


		rc = fill_nic_context(subsys, nic_list[nic_idx], context);
		rc |= fill_tgt_context(subsys, target_list[tgt_idx], context);
		fill_initiator_context(subsys, context);
	}
free:
	deallocate_lists();
	return rc;
}
