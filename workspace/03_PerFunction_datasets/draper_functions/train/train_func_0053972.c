fm10k_mbx_process_connect(struct fm10k_hw *hw,
				     struct fm10k_mbx_info *mbx)
{
	const enum fm10k_mbx_state state = mbx->state;
	const u32 *hdr = &mbx->mbx_hdr;
	u16 size, head;


	size = FM10K_MSG_HDR_FIELD_GET(*hdr, CONNECT_SIZE);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);

	switch (state) {
	case FM10K_STATE_DISCONNECT:
	case FM10K_STATE_OPEN:

		fm10k_mbx_connect_reset(mbx);
		break;
	case FM10K_STATE_CONNECT:

		if (size > mbx->rx.size) {
			mbx->max_size = mbx->rx.size - 1;
		} else {

			mbx->state = FM10K_STATE_OPEN;

			fm10k_mbx_update_max_size(mbx, size);
		}
		break;
	default:
		break;
	}


	mbx->tail = head;

	return fm10k_mbx_create_reply(hw, mbx, head);
}
