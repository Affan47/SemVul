_dmraid_read(struct lib_context *lc,
	     struct dev_info *di, struct dmraid_format *fmt)
{
	struct raid_dev *rd;

	log_notice(lc, "%s: %-7s discovering", di->path, fmt->name);
	if ((rd = fmt->read(lc, di))) {
		log_notice(lc, "%s: %s metadata discovered",
			   di->path, fmt->name);
		rd->fmt = fmt;
	}

	return rd;
}
