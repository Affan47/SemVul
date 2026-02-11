bnxt_init_vnics(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->nr_vnics; i++) {
		struct bnxt_vnic_info *vnic = &bp->vnic_info[i];

		vnic->fw_vnic_id = INVALID_HW_RING_ID;
		vnic->fw_rss_cos_lb_ctx[0] = INVALID_HW_RING_ID;
		vnic->fw_rss_cos_lb_ctx[1] = INVALID_HW_RING_ID;
		vnic->fw_l2_ctx_id = INVALID_HW_RING_ID;

		if (bp->vnic_info[i].rss_hash_key) {
			if (i == 0)
				prandom_bytes(vnic->rss_hash_key,
					      HW_HASH_KEY_SIZE);
			else
				memcpy(vnic->rss_hash_key,
				       bp->vnic_info[0].rss_hash_key,
				       HW_HASH_KEY_SIZE);
		}
	}
}
