usnic_uiom_insert_interval(struct rb_root *root, unsigned long start,
				unsigned long last, int flags)
{
	struct usnic_uiom_interval_node *interval, *tmp;
	unsigned long istart, ilast;
	int iref_cnt, iflags;
	unsigned long lpivot = start;
	int err = 0;
	LIST_HEAD(to_add);
	LIST_HEAD(intersection_set);

	find_intervals_intersection_sorted(root, start, last,
						&intersection_set);

	list_for_each_entry(interval, &intersection_set, link) {


		istart = interval->start;
		ilast = interval->last;
		iref_cnt = interval->ref_cnt;
		iflags = interval->flags;

		if (istart < lpivot) {
			MAKE_NODE_AND_APPEND(tmp, istart, lpivot - 1, iref_cnt,
						iflags, err, err_out, &to_add);
		} else if (istart > lpivot) {
			MAKE_NODE_AND_APPEND(tmp, lpivot, istart - 1, 1, flags,
						err, err_out, &to_add);
			lpivot = istart;
		} else {
			lpivot = istart;
		}

		if (ilast > last) {
			MAKE_NODE_AND_APPEND(tmp, lpivot, last, iref_cnt + 1,
						iflags | flags, err, err_out,
						&to_add);
			MAKE_NODE_AND_APPEND(tmp, last + 1, ilast, iref_cnt,
						iflags, err, err_out, &to_add);
		} else {
			MAKE_NODE_AND_APPEND(tmp, lpivot, ilast, iref_cnt + 1,
						iflags | flags, err, err_out,
						&to_add);
		}

		lpivot = ilast + 1;
	}

	if (lpivot <= last)
		MAKE_NODE_AND_APPEND(tmp, lpivot, last, 1, flags, err, err_out,
					&to_add);

	list_for_each_entry_safe(interval, tmp, &intersection_set, link) {
		usnic_uiom_interval_tree_remove(interval, root);
		kfree(interval);
	}

	list_for_each_entry(interval, &to_add, link)
		usnic_uiom_interval_tree_insert(interval, root);

	return 0;

err_out:
	list_for_each_entry_safe(interval, tmp, &to_add, link)
		kfree(interval);

	return err;
}
