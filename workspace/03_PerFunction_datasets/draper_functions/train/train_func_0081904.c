alloc_send_rmpp_list(struct ib_mad_send_wr_private *send_wr,
				size_t mad_size, gfp_t gfp_mask)
{
	struct ib_mad_send_buf *send_buf = &send_wr->send_buf;
	struct ib_rmpp_mad *rmpp_mad = send_buf->mad;
	struct ib_rmpp_segment *seg = NULL;
	int left, seg_size, pad;

	send_buf->seg_size = mad_size - send_buf->hdr_len;
	send_buf->seg_rmpp_size = mad_size - IB_MGMT_RMPP_HDR;
	seg_size = send_buf->seg_size;
	pad = send_wr->pad;


	for (left = send_buf->data_len + pad; left > 0; left -= seg_size) {
		seg = kmalloc(sizeof (*seg) + seg_size, gfp_mask);
		if (!seg) {
			dev_err(&send_buf->mad_agent->device->dev,
				"alloc_send_rmpp_segs: RMPP mem alloc failed for len %zd, gfp %#x\n",
				sizeof (*seg) + seg_size, gfp_mask);
			free_send_rmpp_list(send_wr);
			return -ENOMEM;
		}
		seg->num = ++send_buf->seg_count;
		list_add_tail(&seg->list, &send_wr->rmpp_list);
	}


	if (pad)
		memset(seg->data + seg_size - pad, 0, pad);

	rmpp_mad->rmpp_hdr.rmpp_version = send_wr->mad_agent_priv->
					  agent.rmpp_version;
	rmpp_mad->rmpp_hdr.rmpp_type = IB_MGMT_RMPP_TYPE_DATA;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);

	send_wr->cur_seg = container_of(send_wr->rmpp_list.next,
					struct ib_rmpp_segment, list);
	send_wr->last_ack_seg = send_wr->cur_seg;
	return 0;
}
