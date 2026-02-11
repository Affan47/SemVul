ctx_fire_notification(u32 context_id, u32 priv_flags)
{
	u32 i, array_size;
	struct vmci_ctx *sub_ctx;
	struct vmci_handle_arr *subscriber_array;
	struct vmci_handle context_handle =
		vmci_make_handle(context_id, VMCI_EVENT_HANDLER);


	subscriber_array = vmci_handle_arr_create(0);
	if (subscriber_array == NULL)
		return VMCI_ERROR_NO_MEM;


	rcu_read_lock();
	list_for_each_entry_rcu(sub_ctx, &ctx_list.head, list_item) {
		struct vmci_handle_list *node;


		if (vmci_deny_interaction(priv_flags, sub_ctx->priv_flags))
			continue;

		list_for_each_entry_rcu(node, &sub_ctx->notifier_list, node) {
			if (!vmci_handle_is_equal(node->handle, context_handle))
				continue;

			vmci_handle_arr_append_entry(&subscriber_array,
					vmci_make_handle(sub_ctx->cid,
							 VMCI_EVENT_HANDLER));
		}
	}
	rcu_read_unlock();


	array_size = vmci_handle_arr_get_size(subscriber_array);
	for (i = 0; i < array_size; i++) {
		int result;
		struct vmci_event_ctx ev;

		ev.msg.hdr.dst = vmci_handle_arr_get_entry(subscriber_array, i);
		ev.msg.hdr.src = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
						  VMCI_CONTEXT_RESOURCE_ID);
		ev.msg.hdr.payload_size = sizeof(ev) - sizeof(ev.msg.hdr);
		ev.msg.event_data.event = VMCI_EVENT_CTX_REMOVED;
		ev.payload.context_id = context_id;

		result = vmci_datagram_dispatch(VMCI_HYPERVISOR_CONTEXT_ID,
						&ev.msg.hdr, false);
		if (result < VMCI_SUCCESS) {
			pr_devel("Failed to enqueue event datagram (type=%d) for context (ID=0x%x)\n",
				 ev.msg.event_data.event,
				 ev.msg.hdr.dst.context);

		}
	}
	vmci_handle_arr_destroy(subscriber_array);

	return VMCI_SUCCESS;
}
