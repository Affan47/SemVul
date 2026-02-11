bnx2x_free_tx_skbs_queue(struct bnx2x_fastpath *fp)
{
	u8 cos;
	struct bnx2x *bp = fp->bp;

	for_each_cos_in_tx_queue(fp, cos) {
		struct bnx2x_fp_txdata *txdata = fp->txdata_ptr[cos];
		unsigned pkts_compl = 0, bytes_compl = 0;

		u16 sw_prod = txdata->tx_pkt_prod;
		u16 sw_cons = txdata->tx_pkt_cons;

		while (sw_cons != sw_prod) {
			bnx2x_free_tx_pkt(bp, txdata, TX_BD(sw_cons),
					  &pkts_compl, &bytes_compl);
			sw_cons++;
		}

		netdev_tx_reset_queue(
			netdev_get_tx_queue(bp->dev,
					    txdata->txq_index));
	}
}
