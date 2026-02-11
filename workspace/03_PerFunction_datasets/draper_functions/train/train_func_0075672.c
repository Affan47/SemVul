bnx2x_vf_mbx_acquire(struct bnx2x *bp, struct bnx2x_virtf *vf,
				 struct bnx2x_vf_mbx *mbx)
{
	int rc;
	struct vfpf_acquire_tlv *acquire = &mbx->msg->req.acquire;


	DP(BNX2X_MSG_IOV,
	   "VF[%d] ACQUIRE: vfdev_info- vf_id %d, vf_os %d resources- n_rxq-%d, n_txq-%d, n_sbs-%d, n_macs-%d, n_vlans-%d, n_mcs-%d\n",
	   vf->abs_vfid, acquire->vfdev_info.vf_id, acquire->vfdev_info.vf_os,
	   acquire->resc_request.num_rxqs, acquire->resc_request.num_txqs,
	   acquire->resc_request.num_sbs, acquire->resc_request.num_mac_filters,
	   acquire->resc_request.num_vlan_filters,
	   acquire->resc_request.num_mc_filters);


	rc = bnx2x_vf_mbx_acquire_chk_dorq(bp, vf, mbx);
	if (rc) {
		DP(BNX2X_MSG_IOV,
		   "VF [%d] - Can't support acquire request due to doorbell mismatch. Please update VM driver\n",
		   vf->abs_vfid);
		goto out;
	}


	if (bnx2x_vf_mbx_is_windows_vm(bp, &mbx->msg->req.acquire))
		vf->fp_hsi = acquire->vfdev_info.fp_hsi_ver;
	else
		vf->fp_hsi = max_t(u8, acquire->vfdev_info.fp_hsi_ver,
				   ETH_FP_HSI_VER_2);
	if (vf->fp_hsi > ETH_FP_HSI_VERSION) {
		DP(BNX2X_MSG_IOV,
		   "VF [%d] - Can't support acquire request since VF requests a FW version which is too new [%02x > %02x]\n",
		   vf->abs_vfid, acquire->vfdev_info.fp_hsi_ver,
		   ETH_FP_HSI_VERSION);
		rc = -EINVAL;
		goto out;
	}


	rc = bnx2x_vf_acquire(bp, vf, &acquire->resc_request);


	vf->bulletin_map = acquire->bulletin_addr;
	if (acquire->vfdev_info.caps & VF_CAP_SUPPORT_EXT_BULLETIN) {
		DP(BNX2X_MSG_IOV, "VF[%d] supports long bulletin boards\n",
		   vf->abs_vfid);
		vf->cfg_flags |= VF_CFG_EXT_BULLETIN;
	} else {
		vf->cfg_flags &= ~VF_CFG_EXT_BULLETIN;
	}

	if (acquire->vfdev_info.caps & VF_CAP_SUPPORT_VLAN_FILTER) {
		DP(BNX2X_MSG_IOV, "VF[%d] supports vlan filtering\n",
		   vf->abs_vfid);
		vf->cfg_flags |= VF_CFG_VLAN_FILTER;
	} else {
		vf->cfg_flags &= ~VF_CFG_VLAN_FILTER;
	}

out:

	bnx2x_vf_mbx_acquire_resp(bp, vf, mbx, rc);
}
