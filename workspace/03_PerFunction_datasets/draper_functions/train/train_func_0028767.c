_copypercent_disp(struct dm_report *rh __attribute__((unused)),
			     struct dm_pool *mem,
			     struct dm_report_field *field,
			     const void *data, void *private __attribute__((unused)))
{
	const struct logical_volume *lv = (const struct logical_volume *) data;
	percent_t percent;
	uint64_t *sortval;
	char *repstr;

	if (!(sortval = dm_pool_alloc(mem, sizeof(uint64_t)))) {
		log_error("dm_pool_alloc failed");
		return 0;
	}

	if ((!(lv->status & PVMOVE) && !(lv->status & MIRRORED)) ||
	    !lv_mirror_percent(lv->vg->cmd, lv, 0, &percent,
			       NULL) || (percent == PERCENT_INVALID)) {
		*sortval = UINT64_C(0);
		dm_report_field_set_value(field, "", sortval);
		return 1;
	}

	percent = copy_percent(lv);

	if (!(repstr = dm_pool_zalloc(mem, 8))) {
		log_error("dm_pool_alloc failed");
		return 0;
	}

	if (dm_snprintf(repstr, 7, "%.2f", percent_to_float(percent)) < 0) {
		log_error("copy percentage too large");
		return 0;
	}

	*sortval = (uint64_t)(percent * 1000.f);
	dm_report_field_set_value(field, repstr, sortval);

	return 1;
}
