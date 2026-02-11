do_for_each_ref(const char *base, each_ref_fn fn, int trim,
			   int flags, void *cb_data)
{
	int retval = 0;
	struct ref_list *packed = get_packed_refs();
	struct ref_list *loose = get_loose_refs();

	struct ref_list *extra;

	for (extra = extra_refs; extra; extra = extra->next)
		retval = do_one_ref(base, fn, trim, flags, cb_data, extra);

	while (packed && loose) {
		struct ref_list *entry;
		int cmp = strcmp(packed->name, loose->name);
		if (!cmp) {
			packed = packed->next;
			continue;
		}
		if (cmp > 0) {
			entry = loose;
			loose = loose->next;
		} else {
			entry = packed;
			packed = packed->next;
		}
		retval = do_one_ref(base, fn, trim, flags, cb_data, entry);
		if (retval)
			goto end_each;
	}

	for (packed = packed ? packed : loose; packed; packed = packed->next) {
		retval = do_one_ref(base, fn, trim, flags, cb_data, packed);
		if (retval)
			goto end_each;
	}

end_each:
	current_ref = NULL;
	return retval;
}
