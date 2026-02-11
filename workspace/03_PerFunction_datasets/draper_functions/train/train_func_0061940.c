calc_tx_flits(const struct sk_buff *skb)
{
	unsigned int flits;


	if (is_eth_imm(skb))
		return DIV_ROUND_UP(skb->len + sizeof(struct cpl_tx_pkt),
				    sizeof(__be64));


	flits = sgl_len(skb_shinfo(skb)->nr_frags + 1);
	if (skb_shinfo(skb)->gso_size)
		flits += (sizeof(struct fw_eth_tx_pkt_vm_wr) +
			  sizeof(struct cpl_tx_pkt_lso_core) +
			  sizeof(struct cpl_tx_pkt_core)) / sizeof(__be64);
	else
		flits += (sizeof(struct fw_eth_tx_pkt_vm_wr) +
			  sizeof(struct cpl_tx_pkt_core)) / sizeof(__be64);
	return flits;
}
