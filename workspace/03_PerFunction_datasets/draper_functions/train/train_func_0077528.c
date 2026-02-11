netvsc_receive(struct netvsc_device *net_device,
			struct vmbus_channel *channel,
			struct hv_device *device,
			struct vmpacket_descriptor *packet)
{
	struct vmtransfer_page_packet_header *vmxferpage_packet;
	struct nvsp_message *nvsp_packet;
	struct hv_netvsc_packet nv_pkt;
	struct hv_netvsc_packet *netvsc_packet = &nv_pkt;
	u32 status = NVSP_STAT_SUCCESS;
	int i;
	int count = 0;
	struct net_device *ndev = hv_get_drvdata(device);
	void *data;
	int ret;
	struct recv_comp_data *rcd;
	u16 q_idx = channel->offermsg.offer.sub_channel_index;


	if (packet->type != VM_PKT_DATA_USING_XFER_PAGES) {
		netdev_err(ndev, "Unknown packet type received - %d\n",
			   packet->type);
		return;
	}

	nvsp_packet = (struct nvsp_message *)((unsigned long)packet +
			(packet->offset8 << 3));


	if (nvsp_packet->hdr.msg_type !=
	    NVSP_MSG1_TYPE_SEND_RNDIS_PKT) {
		netdev_err(ndev, "Unknown nvsp packet type received-"
			" %d\n", nvsp_packet->hdr.msg_type);
		return;
	}

	vmxferpage_packet = (struct vmtransfer_page_packet_header *)packet;

	if (vmxferpage_packet->xfer_pageset_id != NETVSC_RECEIVE_BUFFER_ID) {
		netdev_err(ndev, "Invalid xfer page set id - "
			   "expecting %x got %x\n", NETVSC_RECEIVE_BUFFER_ID,
			   vmxferpage_packet->xfer_pageset_id);
		return;
	}

	count = vmxferpage_packet->range_cnt;


	for (i = 0; i < count; i++) {

		data = (void *)((unsigned long)net_device->
			recv_buf + vmxferpage_packet->ranges[i].byte_offset);
		netvsc_packet->total_data_buflen =
					vmxferpage_packet->ranges[i].byte_count;


		status = rndis_filter_receive(device, netvsc_packet, &data,
					      channel);
	}

	if (!net_device->mrc[q_idx].buf) {
		ret = netvsc_send_recv_completion(channel,
						  vmxferpage_packet->d.trans_id,
						  status);
		if (ret)
			netdev_err(ndev, "Recv_comp q:%hd, tid:%llx, err:%d\n",
				   q_idx, vmxferpage_packet->d.trans_id, ret);
		return;
	}

	rcd = get_recv_comp_slot(net_device, channel, q_idx);

	if (!rcd) {
		netdev_err(ndev, "Recv_comp full buf q:%hd, tid:%llx\n",
			   q_idx, vmxferpage_packet->d.trans_id);
		return;
	}

	rcd->tid = vmxferpage_packet->d.trans_id;
	rcd->status = status;
}
