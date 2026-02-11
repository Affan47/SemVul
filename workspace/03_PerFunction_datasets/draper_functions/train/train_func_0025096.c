vmballoon_reset(struct vmballoon *b)
{
	int error;

	vmballoon_vmci_cleanup(b);


	vmballoon_pop(b);

	if (!vmballoon_send_start(b, VMW_BALLOON_CAPABILITIES))
		return;

	if ((b->capabilities & VMW_BALLOON_BATCHED_CMDS) != 0) {
		b->ops = &vmballoon_batched_ops;
		b->batch_max_pages = VMW_BALLOON_BATCH_MAX_PAGES;
		if (!vmballoon_init_batching(b)) {


			vmballoon_send_start(b, 0);
			return;
		}
	} else if ((b->capabilities & VMW_BALLOON_BASIC_CMDS) != 0) {
		b->ops = &vmballoon_basic_ops;
		b->batch_max_pages = 1;
	}

	b->reset_required = false;

	error = vmballoon_vmci_init(b);
	if (error)
		pr_err("failed to initialize vmci doorbell\n");

	if (!vmballoon_send_guest_id(b))
		pr_err("failed to send guest ID to the host\n");
}
