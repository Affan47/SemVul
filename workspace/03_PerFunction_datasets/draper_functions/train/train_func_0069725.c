bnx2_get_tx_msi(bnx2_t *bp)
{
	struct status_block *sblk = bp->status_blk.msi;
	__u16 tx_cons;

	msync(sblk, sizeof(*sblk), MS_SYNC);
	tx_cons = BNX2_SBLK_EVEN_IDX(sblk->tx2);
	barrier();
	if ((tx_cons & (MAX_TX_DESC_CNT)) == (MAX_TX_DESC_CNT))
		tx_cons++;

	return tx_cons;
}
