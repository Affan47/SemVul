match_hd_array(struct raid_set *rs, struct isw *isw)
{
	int broken = 0, found = 0;

	struct raid_dev *rd;


	list_for_each_entry(rd, &rs->devs, devs) {
		if (_get_disk(isw, rd->di))
			found++;
	}

	return isw->num_disks == broken + found && found == rs->total_devs;
}
