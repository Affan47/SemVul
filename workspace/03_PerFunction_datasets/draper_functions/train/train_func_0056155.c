qp_broker_alloc(struct vmci_handle handle,
			   u32 peer,
			   u32 flags,
			   u32 priv_flags,
			   u64 produce_size,
			   u64 consume_size,
			   struct vmci_qp_page_store *page_store,
			   struct vmci_ctx *context,
			   vmci_event_release_cb wakeup_cb,
			   void *client_data,
			   struct qp_broker_entry **ent,
			   bool *swap)
{
	const u32 context_id = vmci_ctx_get_id(context);
	bool create;
	struct qp_broker_entry *entry = NULL;
	bool is_local = flags & VMCI_QPFLAG_LOCAL;
	int result;

	if (vmci_handle_is_invalid(handle) ||
	    (flags & ~VMCI_QP_ALL_FLAGS) || is_local ||
	    !(produce_size || consume_size) ||
	    !context || context_id == VMCI_INVALID_ID ||
	    handle.context == VMCI_INVALID_ID) {
		return VMCI_ERROR_INVALID_ARGS;
	}

	if (page_store && !VMCI_QP_PAGESTORE_IS_WELLFORMED(page_store))
		return VMCI_ERROR_INVALID_ARGS;


	mutex_lock(&qp_broker_list.mutex);

	if (!is_local && vmci_ctx_qp_exists(context, handle)) {
		pr_devel("Context (ID=0x%x) already attached to queue pair (handle=0x%x:0x%x)\n",
			 context_id, handle.context, handle.resource);
		mutex_unlock(&qp_broker_list.mutex);
		return VMCI_ERROR_ALREADY_EXISTS;
	}

	if (handle.resource != VMCI_INVALID_ID)
		entry = qp_broker_handle_to_entry(handle);

	if (!entry) {
		create = true;
		result =
		    qp_broker_create(handle, peer, flags, priv_flags,
				     produce_size, consume_size, page_store,
				     context, wakeup_cb, client_data, ent);
	} else {
		create = false;
		result =
		    qp_broker_attach(entry, peer, flags, priv_flags,
				     produce_size, consume_size, page_store,
				     context, wakeup_cb, client_data, ent);
	}

	mutex_unlock(&qp_broker_list.mutex);

	if (swap)
		*swap = (context_id == VMCI_HOST_CONTEXT_ID) &&
		    !(create && is_local);

	return result;
}
