time_parse(struct xt_option_call *cb)
{
	struct xt_time_info *info = cb->data;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_DATE_START:
		info->date_start = time_parse_date(cb->arg, false);
		break;
	case O_DATE_STOP:
		info->date_stop = time_parse_date(cb->arg, true);
		break;
	case O_TIME_START:
		info->daytime_start = time_parse_minutes(cb->arg);
		break;
	case O_TIME_STOP:
		info->daytime_stop = time_parse_minutes(cb->arg);
		break;
	case O_TIME_CONTIGUOUS:
		info->flags |= XT_TIME_CONTIGUOUS;
		break;
	case O_LOCAL_TZ:
		fprintf(stderr, "WARNING: --localtz is being replaced by "
		        "--kerneltz, since \"local\" is ambiguous. Note the "
		        "kernel timezone has caveats - "
		        "see manpage for details.\n");

	case O_KERNEL_TZ:
		info->flags |= XT_TIME_LOCAL_TZ;
		break;
	case O_MONTHDAYS:
		info->monthdays_match = time_parse_monthdays(cb->arg);
		if (cb->invert)
			info->monthdays_match ^= XT_TIME_ALL_MONTHDAYS;
		break;
	case O_WEEKDAYS:
		info->weekdays_match = time_parse_weekdays(cb->arg);
		if (cb->invert)
			info->weekdays_match ^= XT_TIME_ALL_WEEKDAYS;
		break;
	}
}
