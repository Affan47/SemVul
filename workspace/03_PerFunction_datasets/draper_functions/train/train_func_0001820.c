ixgbe_is_non_eop(struct ixgbe_ring *rx_ring,
			     union ixgbe_adv_rx_desc *rx_desc,
			     struct sk_buff *skb)
{
	u32 ntc = rx_ring->next_to_clean + 1;


	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IXGBE_RX_DESC(rx_ring, ntc));


	if (ring_is_rsc_enabled(rx_ring)) {
		__le32 rsc_enabled = rx_desc->wb.lower.lo_dword.data &
				     cpu_to_le32(IXGBE_RXDADV_RSCCNT_MASK);

		if (unlikely(rsc_enabled)) {
			u32 rsc_cnt = le32_to_cpu(rsc_enabled);

			rsc_cnt >>= IXGBE_RXDADV_RSCCNT_SHIFT;
			IXGBE_CB(skb)->append_cnt += rsc_cnt - 1;


			ntc = le32_to_cpu(rx_desc->wb.upper.status_error);
			ntc &= IXGBE_RXDADV_NEXTP_MASK;
			ntc >>= IXGBE_RXDADV_NEXTP_SHIFT;
		}
	}


	if (likely(ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP)))
		return false;


	rx_ring->rx_buffer_info[ntc].skb = skb;
	rx_ring->rx_stats.non_eop_descs++;

	return true;
}
