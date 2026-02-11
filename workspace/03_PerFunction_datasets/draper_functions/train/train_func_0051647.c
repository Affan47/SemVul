vmci_guest_cid_update(u32 sub_id,
				  const struct vmci_event_data *event_data,
				  void *client_data)
{
	const struct vmci_event_payld_ctx *ev_payload =
				vmci_event_data_const_payload(event_data);

	if (sub_id != ctx_update_sub_id) {
		pr_devel("Invalid subscriber (ID=0x%x)\n", sub_id);
		return;
	}

	if (!event_data || ev_payload->context_id == VMCI_INVALID_ID) {
		pr_devel("Invalid event data\n");
		return;
	}

	pr_devel("Updating context from (ID=0x%x) to (ID=0x%x) on event (type=%d)\n",
		 vm_context_id, ev_payload->context_id, event_data->event);

	vm_context_id = ev_payload->context_id;
}
