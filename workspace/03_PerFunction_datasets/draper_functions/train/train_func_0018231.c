netvsc_chk_recv_comp(struct netvsc_device *nvdev,
				 struct vmbus_channel *channel, u16 q_idx)
{
	struct recv_comp_data *rcd;
	int ret;

	while (true) {
		rcd = read_recv_comp_slot(nvdev, q_idx);
		if (!rcd)
			break;

		ret = netvsc_send_recv_completion(channel, rcd->tid,
						  rcd->status);
		if (ret)
			break;

		put_recv_comp_slot(nvdev, q_idx);
	}
}
