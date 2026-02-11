interval_restore_expired_ranges(struct live_interval *it)
{
	struct live_range *this, *next;

	list_for_each_entry_safe(this, next, &it->expired_range_list, range_list_node) {
		list_move(&this->range_list_node, &it->range_list);
	}
}
