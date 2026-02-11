bnxt_poll_loopback(struct bnxt *bp, int pkt_size)
{
	struct bnxt_napi *bnapi = bp->bnapi[0];
	struct bnxt_cp_ring_info *cpr;
	struct tx_cmp *txcmp;
	int rc = -EIO;
	u32 raw_cons;
	u32 cons;
	int i;

	cpr = &bnapi->cp_ring;
	raw_cons = cpr->cp_raw_cons;
	for (i = 0; i < 200; i++) {
		cons = RING_CMP(raw_cons);
		txcmp = &cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)];

		if (!TX_CMP_VALID(txcmp, raw_cons)) {
			udelay(5);
			continue;
		}


		dma_rmb();
		if (TX_CMP_TYPE(txcmp) == CMP_TYPE_RX_L2_CMP) {
			rc = bnxt_rx_loopback(bp, bnapi, raw_cons, pkt_size);
			raw_cons = NEXT_RAW_CMP(raw_cons);
			raw_cons = NEXT_RAW_CMP(raw_cons);
			break;
		}
		raw_cons = NEXT_RAW_CMP(raw_cons);
	}
	cpr->cp_raw_cons = raw_cons;
	return rc;
}
