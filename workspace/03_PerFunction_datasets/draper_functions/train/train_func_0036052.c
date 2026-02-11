vmballoon_send_start(struct vmballoon *b, unsigned long req_caps)
{
	unsigned long status, capabilities, dummy = 0;
	bool success;

	STATS_INC(b->stats.start);

	status = VMWARE_BALLOON_CMD(START, req_caps, dummy, capabilities);

	switch (status) {
	case VMW_BALLOON_SUCCESS_WITH_CAPABILITIES:
		b->capabilities = capabilities;
		success = true;
		break;
	case VMW_BALLOON_SUCCESS:
		b->capabilities = VMW_BALLOON_BASIC_CMDS;
		success = true;
		break;
	default:
		success = false;
	}

	if (b->capabilities & VMW_BALLOON_BATCHED_2M_CMDS)
		b->supported_page_sizes = 2;
	else
		b->supported_page_sizes = 1;

	if (!success) {
		pr_debug("%s - failed, hv returns %ld\n", __func__, status);
		STATS_INC(b->stats.start_fail);
	}
	return success;
}
