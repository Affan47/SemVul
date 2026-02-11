bnxt_hwrm_stat_ctx_free(struct bnxt *bp)
{
	int rc = 0, i;
	struct hwrm_stat_ctx_free_input req = {0};

	if (!bp->bnapi)
		return 0;

	if (BNXT_CHIP_TYPE_NITRO_A0(bp))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_STAT_CTX_FREE, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		if (cpr->hw_stats_ctx_id != INVALID_STATS_CTX_ID) {
			req.stat_ctx_id = cpu_to_le32(cpr->hw_stats_ctx_id);

			rc = _hwrm_send_message(bp, &req, sizeof(req),
						HWRM_CMD_TIMEOUT);
			if (rc)
				break;

			cpr->hw_stats_ctx_id = INVALID_STATS_CTX_ID;
		}
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
