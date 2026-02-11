igbvf_rx_checksum_adv(struct igbvf_adapter *adapter,
					 u32 status_err, struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);


	if ((status_err & E1000_RXD_STAT_IXSM) ||
	    (adapter->flags & IGBVF_FLAG_RX_CSUM_DISABLED))
		return;


	if (status_err &
	    (E1000_RXDEXT_STATERR_TCPE | E1000_RXDEXT_STATERR_IPE)) {

		adapter->hw_csum_err++;
		return;
	}


	if (status_err & (E1000_RXD_STAT_TCPCS | E1000_RXD_STAT_UDPCS))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	adapter->hw_csum_good++;
}
