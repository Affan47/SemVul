bnad_netdev_qstats_fill(struct bnad *bnad, struct rtnl_link_stats64 *stats)
{
	int i, j;

	for (i = 0; i < bnad->num_rx; i++) {
		for (j = 0; j < bnad->num_rxp_per_rx; j++) {
			if (bnad->rx_info[i].rx_ctrl[j].ccb) {
				stats->rx_packets += bnad->rx_info[i].
				rx_ctrl[j].ccb->rcb[0]->rxq->rx_packets;
				stats->rx_bytes += bnad->rx_info[i].
					rx_ctrl[j].ccb->rcb[0]->rxq->rx_bytes;
				if (bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
					bnad->rx_info[i].rx_ctrl[j].ccb->
					rcb[1]->rxq) {
					stats->rx_packets +=
						bnad->rx_info[i].rx_ctrl[j].
						ccb->rcb[1]->rxq->rx_packets;
					stats->rx_bytes +=
						bnad->rx_info[i].rx_ctrl[j].
						ccb->rcb[1]->rxq->rx_bytes;
				}
			}
		}
	}
	for (i = 0; i < bnad->num_tx; i++) {
		for (j = 0; j < bnad->num_txq_per_tx; j++) {
			if (bnad->tx_info[i].tcb[j]) {
				stats->tx_packets +=
				bnad->tx_info[i].tcb[j]->txq->tx_packets;
				stats->tx_bytes +=
					bnad->tx_info[i].tcb[j]->txq->tx_bytes;
			}
		}
	}
}
