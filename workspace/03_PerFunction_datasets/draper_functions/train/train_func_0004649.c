bnx2x_vf_mbx_acquire_chk_dorq(struct bnx2x *bp,
					 struct bnx2x_virtf *vf,
					 struct bnx2x_vf_mbx *mbx)
{


	if (bnx2x_search_tlv_list(bp, &mbx->msg->req,
				  CHANNEL_TLV_PHYS_PORT_ID))
		return 0;


	if (bnx2x_vf_mbx_is_windows_vm(bp, &mbx->msg->req.acquire))
		return 0;

	return -EOPNOTSUPP;
}
