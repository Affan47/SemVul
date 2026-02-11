write_imm(struct tx_desc *d, struct sk_buff *skb,
			     unsigned int len, unsigned int gen)
{
	struct work_request_hdr *from = (struct work_request_hdr *)skb->data;
	struct work_request_hdr *to = (struct work_request_hdr *)d;

	if (likely(!skb->data_len))
		memcpy(&to[1], &from[1], len - sizeof(*from));
	else
		skb_copy_bits(skb, sizeof(*from), &to[1], len - sizeof(*from));

	to->wr_hi = from->wr_hi | htonl(F_WR_SOP | F_WR_EOP |
					V_WR_BCNTLFLT(len & 7));
	dma_wmb();
	to->wr_lo = from->wr_lo | htonl(V_WR_GEN(gen) |
					V_WR_LEN((len + 7) / 8));
	wr_gen2(d, gen);
	kfree_skb(skb);
}
