copy_callback(int read_err, unsigned long write_err, void *context)
{
	struct dm_snap_pending_exception *pe = context;
	struct dm_snapshot *s = pe->snap;

	pe->copy_error = read_err || write_err;

	if (pe->exception_sequence == s->exception_complete_sequence) {
		s->exception_complete_sequence++;
		complete_exception(pe);

		while (!list_empty(&s->out_of_order_list)) {
			pe = list_entry(s->out_of_order_list.next,
					struct dm_snap_pending_exception, out_of_order_entry);
			if (pe->exception_sequence != s->exception_complete_sequence)
				break;
			s->exception_complete_sequence++;
			list_del(&pe->out_of_order_entry);
			complete_exception(pe);
		}
	} else {
		struct list_head *lh;
		struct dm_snap_pending_exception *pe2;

		list_for_each_prev(lh, &s->out_of_order_list) {
			pe2 = list_entry(lh, struct dm_snap_pending_exception, out_of_order_entry);
			if (pe2->exception_sequence < pe->exception_sequence)
				break;
		}
		list_add(&pe->out_of_order_entry, lh);
	}
}
