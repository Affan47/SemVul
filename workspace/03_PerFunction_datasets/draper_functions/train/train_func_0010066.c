fm10k_sm_mbx_create_reply(struct fm10k_hw *hw,
				      struct fm10k_mbx_info *mbx, u16 head)
{
	switch (mbx->state) {
	case FM10K_STATE_OPEN:
	case FM10K_STATE_DISCONNECT:

		fm10k_sm_mbx_transmit(hw, mbx, head);


		if (mbx->tail_len || (mbx->state == FM10K_STATE_OPEN)) {
			fm10k_sm_mbx_create_data_hdr(mbx);
		} else {
			mbx->remote = 0;
			fm10k_sm_mbx_create_connect_hdr(mbx, 0);
		}
		break;
	case FM10K_STATE_CONNECT:
	case FM10K_STATE_CLOSED:
		fm10k_sm_mbx_create_connect_hdr(mbx, 0);
		break;
	default:
		break;
	}
}
