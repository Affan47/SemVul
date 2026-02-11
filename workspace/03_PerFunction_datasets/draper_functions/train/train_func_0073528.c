bnx2x_start_xmit(nic_t *nic, size_t len, u16_t vlan_id)
{
	bnx2x_t *bp = (bnx2x_t *) nic->priv;
	uint16_t ring_prod;
	struct eth_tx_start_bd *txbd;
	struct eth_tx_bd *txbd2;
	struct eth_rx_bd *rx_bd;
	rx_bd = (struct eth_rx_bd *)(((__u8 *) bp->tx_ring) + nic->page_size);

	if ((rx_bd->addr_hi == 0) && (rx_bd->addr_lo == 0)) {
		LOG_PACKET(PFX "%s: trying to transmit when device is closed",
			   nic->log_name);
		pthread_mutex_unlock(&nic->xmit_mutex);
		return;
	}

	ring_prod = BNX2X_TX_RING_IDX(bp->tx_bd_prod);
	txbd = &bp->tx_ring[ring_prod];

	BNX2X_SET_TX_VLAN(bp, txbd, vlan_id);

	bp->tx_prod++;
	bp->tx_bd_prod = BNX2X_NEXT_TX_BD(bp->tx_bd_prod);
	bp->tx_bd_prod = BNX2X_NEXT_TX_BD(bp->tx_bd_prod);

	ring_prod = BNX2X_TX_RING_IDX(bp->tx_bd_prod);
	txbd2 = (struct eth_tx_bd *)&bp->tx_ring[ring_prod];

	txbd2->nbytes = len - 0x10;
	txbd2->total_pkt_bytes = len;

	bp->tx_bd_prod = BNX2X_NEXT_TX_BD(bp->tx_bd_prod);

	barrier();
	if (nic->nl_process_if_down == 0) {
		bnx2x_doorbell(bp, bp->tx_doorbell, 0x02 |
			       (bp->tx_bd_prod << 16));
		bnx2x_flush_doorbell(bp, bp->tx_doorbell);
	} else {


		pthread_mutex_unlock(&nic->xmit_mutex);
	}
	LOG_PACKET(PFX "%s: sent %d bytes using bp->tx_prod: %d",
		   nic->log_name, len, bp->tx_prod);
}
