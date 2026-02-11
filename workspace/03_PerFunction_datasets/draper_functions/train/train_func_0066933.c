qp_list_find(struct qp_list *qp_list,
				     struct vmci_handle handle)
{
	struct qp_entry *entry;

	if (vmci_handle_is_invalid(handle))
		return NULL;

	list_for_each_entry(entry, &qp_list->head, list_item) {
		if (vmci_handle_is_equal(entry->handle, handle))
			return entry;
	}

	return NULL;
}
