replace_system_preds(struct trace_subsystem_dir *dir,
				struct trace_array *tr,
				struct filter_parse_state *ps,
				char *filter_string)
{
	struct trace_event_file *file;
	struct filter_list *filter_item;
	struct filter_list *tmp;
	LIST_HEAD(filter_list);
	bool fail = true;
	int err;

	list_for_each_entry(file, &tr->events, list) {
		if (file->system != dir)
			continue;


		err = replace_preds(file->event_call, NULL, ps, true);
		if (err)
			event_set_no_set_filter_flag(file);
		else
			event_clear_no_set_filter_flag(file);
	}

	list_for_each_entry(file, &tr->events, list) {
		struct event_filter *filter;

		if (file->system != dir)
			continue;

		if (event_no_set_filter_flag(file))
			continue;

		filter_item = kzalloc(sizeof(*filter_item), GFP_KERNEL);
		if (!filter_item)
			goto fail_mem;

		list_add_tail(&filter_item->list, &filter_list);

		filter_item->filter = __alloc_filter();
		if (!filter_item->filter)
			goto fail_mem;
		filter = filter_item->filter;


		err = replace_filter_string(filter, filter_string);
		if (err)
			goto fail_mem;

		err = replace_preds(file->event_call, filter, ps, false);
		if (err) {
			filter_disable(file);
			parse_error(ps, FILT_ERR_BAD_SUBSYS_FILTER, 0);
			append_filter_err(ps, filter);
		} else
			event_set_filtered_flag(file);


		filter = event_filter(file);
		event_set_filter(file, filter_item->filter);
		filter_item->filter = filter;

		fail = false;
	}

	if (fail)
		goto fail;


	synchronize_sched();
	list_for_each_entry_safe(filter_item, tmp, &filter_list, list) {
		__free_filter(filter_item->filter);
		list_del(&filter_item->list);
		kfree(filter_item);
	}
	return 0;
 fail:

	list_for_each_entry_safe(filter_item, tmp, &filter_list, list) {
		list_del(&filter_item->list);
		kfree(filter_item);
	}
	parse_error(ps, FILT_ERR_BAD_SUBSYS_FILTER, 0);
	return -EINVAL;
 fail_mem:

	if (!fail)
		synchronize_sched();
	list_for_each_entry_safe(filter_item, tmp, &filter_list, list) {
		__free_filter(filter_item->filter);
		list_del(&filter_item->list);
		kfree(filter_item);
	}
	return -ENOMEM;
}
