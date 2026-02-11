list_flashnodes(int info_level, uint32_t host_no)
{
	int rc = 0;
	int num_found = 0;

	rc = iscsi_sysfs_for_each_flashnode(NULL, host_no, &num_found,
					    flashnode_info_print_flat);

	if (!num_found) {
		log_error("No flashnodes attached to host %u.", host_no);
		rc = ISCSI_ERR_NO_OBJS_FOUND;
	}

	return rc;
}
