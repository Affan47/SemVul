bnx2_start_xmit(nic_t *nic, size_t len, u16_t vlan_id)
{
	bnx2_t *bp = (bnx2_t *) nic->priv;
	uint16_t ring_prod;
	struct tx_bd *txbd;
	struct rx_bd *rxbd;
	rxbd = (struct rx_bd *)(((__u8 *) bp->tx_ring) + nic->page_size);

	if ((rxbd->rx_bd_haddr_hi == 0) && (rxbd->rx_bd_haddr_lo == 0)) {
		LOG_PACKET(PFX "%s: trying to transmit when device is closed",
			   nic->log_name);
		pthread_mutex_unlock(&nic->xmit_mutex);
		return;
	}

	ring_prod = TX_RING_IDX(bp->tx_prod);
	txbd = &bp->tx_ring[ring_prod];

	txbd->tx_bd_mss_nbytes = len;

	if (vlan_id) {
		txbd->tx_bd_vlan_tag_flags = (vlan_id << 16) |
		    TX_BD_FLAGS_VLAN_TAG | TX_BD_FLAGS_END | TX_BD_FLAGS_START;
	} else
		txbd->tx_bd_vlan_tag_flags = TX_BD_FLAGS_END |
		    TX_BD_FLAGS_START;

	bp->tx_bseq += len;
	bp->tx_prod = NEXT_TX_BD(bp->tx_prod);

	bnx2_wr16(bp, bp->tx_bidx_io, bp->tx_prod);
	bnx2_wr32(bp, bp->tx_bseq_io, bp->tx_bseq);

	bnx2_reg_sync(bp, bp->tx_bidx_io, sizeof(__u16));
	bnx2_reg_sync(bp, bp->tx_bseq_io, sizeof(__u32));

	LOG_PACKET(PFX "%s: sent %d bytes using dev->tx_prod: %d",
		   nic->log_name, len, bp->tx_prod);
}
