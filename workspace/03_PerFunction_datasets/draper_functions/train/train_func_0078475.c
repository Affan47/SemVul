tx_birq(struct bchannel *bch)
{
	if (bch->tx_skb && bch->tx_idx < bch->tx_skb->len)
		hfcpci_fill_fifo(bch);
	else {
		if (bch->tx_skb)
			dev_kfree_skb(bch->tx_skb);
		if (get_next_bframe(bch))
			hfcpci_fill_fifo(bch);
	}
}
