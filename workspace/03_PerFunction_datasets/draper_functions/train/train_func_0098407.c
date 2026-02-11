get_recv_comp_slot(
	struct netvsc_device *nvdev, struct vmbus_channel *channel, u16 q_idx)
{
	u32 filled, avail, next;
	struct recv_comp_data *rcd;

	if (!nvdev->recv_section)
		return NULL;

	if (!nvdev->mrc[q_idx].buf)
		return NULL;

	if (atomic_read(&nvdev->num_outstanding_recvs) >
	    nvdev->recv_section->num_sub_allocs * NETVSC_RCD_WATERMARK / 100)
		netvsc_chk_recv_comp(nvdev, channel, q_idx);

	count_recv_comp_slot(nvdev, q_idx, &filled, &avail);
	if (!avail)
		return NULL;

	next = nvdev->mrc[q_idx].next;
	rcd = nvdev->mrc[q_idx].buf + next * sizeof(struct recv_comp_data);
	nvdev->mrc[q_idx].next = (next + 1) % NETVSC_RECVSLOT_MAX;

	atomic_inc(&nvdev->num_outstanding_recvs);

	return rcd;
}
