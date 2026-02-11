log_disk(struct lib_context *lc, struct list_head *pos)
{
	struct dev_info *di = list_entry(pos, typeof(*di), list);

	if (OPT_STR_COLUMN(lc)) {
		const struct log_handler log_handlers[] = {
			{"devpath", 1, log_string, di->path},
			{"path", 1, log_string, di->path},
			{"sectors", 3, log_uint64, &di->sectors},
			{"serialnumber", 3, log_string,
			 di->serial ? (void *) di->serial : (void *) "N/A"},
			{"size", 2, log_uint64, &di->sectors},
		};

		log_fields(lc, log_handlers, ARRAY_SIZE(log_handlers));
	}
	else {
		const char *fmt[] = {
			"%s: %12" PRIu64 " total, \"%s\"",
			"%s",
			"%s:%" PRIu64 ":\"%s\"",
		};

		log_print(lc, fmt[ARRAY_LIMIT(fmt, OPT_COLUMN(lc))],
			  di->path, di->sectors,
			  di->serial ? di->serial : "N/A");
	}
}
