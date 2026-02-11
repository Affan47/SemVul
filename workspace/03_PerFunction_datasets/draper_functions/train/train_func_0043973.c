fm10k_mbx_process_data(struct fm10k_hw *hw,
				  struct fm10k_mbx_info *mbx)
{
	const u32 *hdr = &mbx->mbx_hdr;
	u16 head, tail;
	s32 err;


	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);
	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, TAIL);


	if (mbx->state == FM10K_STATE_CONNECT) {
		mbx->tail = head;
		mbx->state = FM10K_STATE_OPEN;
	}


	err = fm10k_mbx_push_tail(hw, mbx, tail);
	if (err < 0)
		return err;


	err = fm10k_mbx_verify_remote_crc(mbx);
	if (err)
		return err;


	fm10k_mbx_dequeue_rx(hw, mbx);

	return fm10k_mbx_create_reply(hw, mbx, head);
}
