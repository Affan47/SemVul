bnxt_hwrm_set_coal(struct bnxt *bp)
{
	int i, rc = 0;
	struct hwrm_ring_cmpl_ring_cfg_aggint_params_input req = {0};
	u16 max_buf, max_buf_irq;
	u16 buf_tmr, buf_tmr_irq;
	u32 flags;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS,
			       -1, -1);


	max_buf = min_t(u16, bp->coal_bufs / 4, 2);

	max_buf = clamp_t(u16, max_buf, 1, 63);
	max_buf_irq = clamp_t(u16, bp->coal_bufs_irq, 1, 63);
	buf_tmr = max_t(u16, bp->coal_ticks / 4, 1);
	buf_tmr_irq = max_t(u16, bp->coal_ticks_irq, 1);

	flags = RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_TIMER_RESET;


	if (BNXT_COAL_TIMER_TO_USEC(bp->coal_ticks) < 25)
		flags |= RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_RING_IDLE;

	req.flags = cpu_to_le16(flags);
	req.num_cmpl_dma_aggr = cpu_to_le16(max_buf);
	req.num_cmpl_dma_aggr_during_int = cpu_to_le16(max_buf_irq);
	req.cmpl_aggr_dma_tmr = cpu_to_le16(buf_tmr);
	req.cmpl_aggr_dma_tmr_during_int = cpu_to_le16(buf_tmr_irq);
	req.int_lat_tmr_min = cpu_to_le16(buf_tmr);
	req.int_lat_tmr_max = cpu_to_le16(bp->coal_ticks);
	req.num_cmpl_aggr_int = cpu_to_le16(bp->coal_bufs);

	mutex_lock(&bp->hwrm_cmd_lock);
	for (i = 0; i < bp->cp_nr_rings; i++) {
		req.ring_id = cpu_to_le16(bp->grp_info[i].cp_fw_ring_id);

		rc = _hwrm_send_message(bp, &req, sizeof(req),
					HWRM_CMD_TIMEOUT);
		if (rc)
			break;
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
