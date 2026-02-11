check_raid_set(struct lib_context *lc, struct raid_set *rs,
	       unsigned int (*f_devices) (struct raid_dev *rd,
					  void *context),
	       void *f_devices_context,
	       int (*f_check) (struct lib_context * lc, struct raid_set * r,
			       struct raid_dev * rd, void *context),
	       void *f_check_context, const char *handler)
{
	struct raid_set *r;
	struct raid_dev *rd;

	list_for_each_entry(r, &rs->sets, list)
		check_raid_set(lc, r, f_devices, f_devices_context,
			       f_check, f_check_context, handler);


	if (!T_GROUP(rs) && DEVS(rs)) {
		rd = list_entry(rs->devs.next, struct raid_dev, devs);


	       if (rd->fmt->metadata_handler)
			rs->status = rd->fmt->metadata_handler(lc, GET_STATUS,
							       NULL, rs);
	       else

			_check_raid_set(lc, rs, f_devices, f_devices_context,
					f_check, f_check_context, handler);
	}


	return set_rs_status(lc, rs);
}
