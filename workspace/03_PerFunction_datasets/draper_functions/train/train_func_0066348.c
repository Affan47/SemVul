lookup_overlapping_address_handler(
	struct list_head *list, unsigned long long offset, size_t length)
{
	struct fw_address_handler *handler;

	list_for_each_entry_rcu(handler, list, link) {
		if (handler->offset < offset + length &&
		    offset < handler->offset + handler->length)
			return handler;
	}

	return NULL;
}
