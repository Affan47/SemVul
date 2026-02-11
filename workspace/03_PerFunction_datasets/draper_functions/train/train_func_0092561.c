group_rd(struct lib_context *lc,
	 struct raid_set *rs_group, struct raid_dev *rd_meta)
{
	unsigned d;
	void *private;
	struct isw *isw = META(rd_meta, isw);
	struct isw_dev *dev;
	struct raid_dev *rd;
	struct raid_set *rs, *ss;
	char *ss_name = NULL;


	if (isw->disk[0].status & SPARE_DISK) {


		dev = NULL;
		if (!(rd = _create_rd(lc, rd_meta, isw, dev)))
			return NULL;

		if (!(rs = find_or_alloc_raid_set(lc, rd->name,
						  FIND_ALL, rd,
						  &rs_group->sets, NULL,
						  NULL))) {
			free_raid_dev(lc, &rd);
			return NULL;
		}

		rs->status = s_ok;
		list_add_sorted(lc, &rs->devs, &rd->devs, dev_sort);
	} else {

		for (d = 0; d < isw->num_raid_devs; d++) {
			dev = raiddev(isw, d);

			if (!(rd = _create_rd(lc, rd_meta, isw, dev)))
				return NULL;
			if (is_raid10(dev)) {
				ss_name = name(lc, rd, dev, N_VOLUME_FORCE);
				ss = find_or_alloc_raid_set(lc, ss_name,
							    FIND_ALL, rd,
							    &rs_group->sets,
							    super_created, dev);

				if (!ss) {
					dbg_free(ss_name);
					free_raid_dev(lc, &rd);
					return NULL;
				}
			} else
				ss = rs_group;

			if (!(rs = find_or_alloc_raid_set(lc, rd->name,
							  FIND_ALL, rd,
							  &ss->sets, create_rs,
							  dev))) {
				free_raid_dev(lc, &rd);
				return NULL;
			}
			if (is_raid10(dev))
				rs->flags |= f_subset;
			rs->status = s_ok;


			private = rd->private.ptr;
			rd->private.ptr = isw;
			list_add_sorted(lc, &rs->devs, &rd->devs, dev_sort);

			rd->private.ptr = private;

		}
	}

	return rs_group;
}
