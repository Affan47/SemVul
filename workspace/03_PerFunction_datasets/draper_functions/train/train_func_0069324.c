brcmf_msgbuf_delete_flowring(struct brcmf_pub *drvr, u8 flowid)
{
	struct brcmf_msgbuf *msgbuf = (struct brcmf_msgbuf *)drvr->proto->pd;
	struct msgbuf_tx_flowring_delete_req *delete;
	struct brcmf_commonring *commonring;
	void *ret_ptr;
	u8 ifidx;
	int err;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_for_write(commonring);
	if (!ret_ptr) {
		brcmf_err("FW unaware, flowring will be removed !!\n");
		brcmf_commonring_unlock(commonring);
		brcmf_msgbuf_remove_flowring(msgbuf, flowid);
		return;
	}

	delete = (struct msgbuf_tx_flowring_delete_req *)ret_ptr;

	ifidx = brcmf_flowring_ifidx_get(msgbuf->flow, flowid);

	delete->msg.msgtype = MSGBUF_TYPE_FLOW_RING_DELETE;
	delete->msg.ifidx = ifidx;
	delete->msg.request_id = 0;

	delete->flow_ring_id = cpu_to_le16(flowid +
					   BRCMF_NROF_H2D_COMMON_MSGRINGS);
	delete->reason = 0;

	brcmf_dbg(MSGBUF, "Send Flow Delete Req flow ID %d, ifindex %d\n",
		  flowid, ifidx);

	err = brcmf_commonring_write_complete(commonring);
	brcmf_commonring_unlock(commonring);
	if (err) {
		brcmf_err("Failed to submit RING_DELETE, flowring will be removed\n");
		brcmf_msgbuf_remove_flowring(msgbuf, flowid);
	}
}
