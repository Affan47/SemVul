e1000_alloc_rx_skb(struct e1000_adapter *adapter,
					  unsigned int bufsz)
{
	struct sk_buff *skb = napi_alloc_skb(&adapter->napi, bufsz);

	if (unlikely(!skb))
		adapter->alloc_rx_buff_failed++;
	return skb;
}
