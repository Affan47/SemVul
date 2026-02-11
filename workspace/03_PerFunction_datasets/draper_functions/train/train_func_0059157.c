vmci_ctx_enqueue_datagram(u32 cid, struct vmci_datagram *dg)
{
	struct vmci_datagram_queue_entry *dq_entry;
	struct vmci_ctx *context;
	struct vmci_handle dg_src;
	size_t vmci_dg_size;

	vmci_dg_size = VMCI_DG_SIZE(dg);
	if (vmci_dg_size > VMCI_MAX_DG_SIZE) {
		pr_devel("Datagram too large (bytes=%Zu)\n", vmci_dg_size);
		return VMCI_ERROR_INVALID_ARGS;
	}


	context = vmci_ctx_get(cid);
	if (!context) {
		pr_devel("Invalid context (ID=0x%x)\n", cid);
		return VMCI_ERROR_INVALID_ARGS;
	}


	dq_entry = kmalloc(sizeof(*dq_entry), GFP_KERNEL);
	if (dq_entry == NULL) {
		pr_warn("Failed to allocate memory for datagram\n");
		vmci_ctx_put(context);
		return VMCI_ERROR_NO_MEM;
	}
	dq_entry->dg = dg;
	dq_entry->dg_size = vmci_dg_size;
	dg_src = dg->src;
	INIT_LIST_HEAD(&dq_entry->list_item);

	spin_lock(&context->lock);


	if (context->datagram_queue_size + vmci_dg_size >=
	    VMCI_MAX_DATAGRAM_QUEUE_SIZE &&
	    (!vmci_handle_is_equal(dg_src,
				vmci_make_handle
				(VMCI_HYPERVISOR_CONTEXT_ID,
				 VMCI_CONTEXT_RESOURCE_ID)) ||
	     context->datagram_queue_size + vmci_dg_size >=
	     VMCI_MAX_DATAGRAM_AND_EVENT_QUEUE_SIZE)) {
		spin_unlock(&context->lock);
		vmci_ctx_put(context);
		kfree(dq_entry);
		pr_devel("Context (ID=0x%x) receive queue is full\n", cid);
		return VMCI_ERROR_NO_RESOURCES;
	}

	list_add(&dq_entry->list_item, &context->datagram_queue);
	context->pending_datagrams++;
	context->datagram_queue_size += vmci_dg_size;
	ctx_signal_notify(context);
	wake_up(&context->host_context.wait_queue);
	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	return vmci_dg_size;
}
