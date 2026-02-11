dm_report_field_string(struct dm_report *rh,
			   struct dm_report_field *field, const char *const *data)
{
	char *repstr;

	if (!(repstr = dm_pool_strdup(rh->mem, *data))) {
		log_error("dm_report_field_string: dm_pool_strdup failed");
		return 0;
	}

	field->report_string = repstr;
	field->sort_value = (const void *) field->report_string;

	return 1;
}
