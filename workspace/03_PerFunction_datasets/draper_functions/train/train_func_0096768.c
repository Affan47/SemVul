vxge_hw_vpath_poll_rx(struct __vxge_hw_ring *ring)
{
	u8 t_code;
	enum vxge_hw_status status = VXGE_HW_OK;
	void *first_rxdh;
	u64 val64 = 0;
	int new_count = 0;

	ring->cmpl_cnt = 0;

	status = vxge_hw_ring_rxd_next_completed(ring, &first_rxdh, &t_code);
	if (status == VXGE_HW_OK)
		ring->callback(ring, first_rxdh,
			t_code, ring->channel.userdata);

	if (ring->cmpl_cnt != 0) {
		ring->doorbell_cnt += ring->cmpl_cnt;
		if (ring->doorbell_cnt >= ring->rxds_limit) {


			new_count = (ring->doorbell_cnt * 4);


			ring->total_db_cnt += ring->doorbell_cnt;
			if (ring->total_db_cnt >= ring->rxds_per_block) {
				new_count += 4;

				ring->total_db_cnt %= ring->rxds_per_block;
			}
			writeq(VXGE_HW_PRC_RXD_DOORBELL_NEW_QW_CNT(new_count),
				&ring->vp_reg->prc_rxd_doorbell);
			val64 =
			  readl(&ring->common_reg->titan_general_int_status);
			ring->doorbell_cnt = 0;
		}
	}

	return status;
}
