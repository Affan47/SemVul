it_nexus_destroy(int tid, uint64_t itn_id)
{
	int i;
	struct it_nexus *itn;
	struct scsi_lu *lu;

	dprintf("%d %" PRIu64 "\n", tid, itn_id);

	itn = it_nexus_lookup(tid, itn_id);
	if (!itn)
		return -ENOENT;

	for (i = 0; i < ARRAY_SIZE(itn->cmd_hash_list); i++)
		if (!list_empty(&itn->cmd_hash_list[i]))
			return -EBUSY;

	list_for_each_entry(lu, &itn->nexus_target->device_list, device_siblings)
		device_release(tid, itn_id, lu->lun, 0);

	it_nexus_del_lu_info(itn);

	list_del(&itn->nexus_siblings);
	free(itn);
	return 0;
}
