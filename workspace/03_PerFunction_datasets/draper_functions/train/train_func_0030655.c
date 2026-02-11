_lvstatus_disp(struct dm_report *rh __attribute__((unused)), struct dm_pool *mem,
			  struct dm_report_field *field,
			  const void *data, void *private __attribute__((unused)))
{
	const struct logical_volume *lv = (const struct logical_volume *) data;
	char *repstr;

	if (!(repstr = lv_attr_dup(mem, lv)))
		return 0;

	dm_report_field_set_value(field, repstr, NULL);
	return 1;
}
