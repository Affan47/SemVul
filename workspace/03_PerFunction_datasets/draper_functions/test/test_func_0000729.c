update_metadata_isw_dev(struct isw *new_isw,
			int failed_disk_idx,
			struct isw *old_isw,
			int isw_dev_idx, unsigned isw_dev_offs)
{
	int i, map_size;
	struct isw_dev *new_dev, *old_dev = raiddev(old_isw, isw_dev_idx);


	memcpy((void *) (new_isw->disk + new_isw->num_disks) +
	       isw_dev_offs, old_dev, sizeof(struct isw_dev));


	new_dev = raiddev(new_isw, isw_dev_idx);
	new_dev->vol.migr_state = ISW_T_MIGR_STATE_MIGRATING;
	new_dev->vol.migr_type = ISW_T_MIGR_TYPE_REBUILDING;


	new_dev->vol.map[0].map_state = ISW_T_STATE_NORMAL;
	new_dev->vol.map[0].failed_disk_num = failed_disk_idx;


	for (i = 0; i < new_isw->num_disks - 1; i++)
		new_dev->vol.map[0].disk_ord_tbl[i] = i;


	map_size =
		sizeof(struct isw_map) + (new_dev->vol.map[0].num_members -
					  1) *
		sizeof(((struct isw_map *) NULL)->disk_ord_tbl);
	memcpy((void *) &new_dev->vol.map[0] + map_size,
	       (void *) &new_dev->vol.map[0], map_size);


	((struct isw_map *)
	 ((void *) &new_dev->vol.map[0]) + map_size)->map_state =
		new_dev->vol.map[0].raid_level == ISW_T_RAID0 ?
		ISW_T_STATE_FAILED : ISW_T_STATE_DEGRADED;

	return (unsigned)
		((unsigned long) (((void*) &new_dev->vol.map[0]) + 2 * map_size)) -
		((unsigned long) new_dev);
}
