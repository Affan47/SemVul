bnx2x_vfpf_update_vlan(struct bnx2x *bp, u16 vid, u8 vf_qid, bool add)
{
	struct vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	struct pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	int rc = 0;

	if (!(bp->acquire_resp.pfdev_info.pf_cap & PFVF_CAP_VLAN_FILTER)) {
		DP(BNX2X_MSG_IOV, "HV does not support vlan filtering\n");
		return 0;
	}


	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			sizeof(*req));

	req->flags = VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED;
	req->vf_qid = vf_qid;
	req->n_mac_vlan_filters = 1;

	req->filters[0].flags = VFPF_Q_FILTER_VLAN_TAG_VALID;

	if (add)
		req->filters[0].flags |= VFPF_Q_FILTER_SET;


	bnx2x_sample_bulletin(bp);

	if (bp->shadow_bulletin.content.valid_bitmap & 1 << VLAN_VALID) {
		BNX2X_ERR("Hypervisor will dicline the request, avoiding\n");
		rc = -EINVAL;
		goto out;
	}

	req->filters[0].vlan_tag = vid;


	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));


	bnx2x_dp_tlv_list(bp, req);


	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	if (rc) {
		BNX2X_ERR("failed to send message to pf. rc was %d\n", rc);
		goto out;
	}

	if (resp->hdr.status != PFVF_STATUS_SUCCESS) {
		BNX2X_ERR("vfpf %s VLAN %d failed\n", add ? "add" : "del",
			  vid);
		rc = -EINVAL;
	}
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	return rc;
}
