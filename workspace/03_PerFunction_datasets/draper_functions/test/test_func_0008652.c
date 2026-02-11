sxgbe_prepare_tx_desc(struct sxgbe_tx_norm_desc *p, u8 is_fd,
				  int buf1_len, int pkt_len, int cksum)
{
	p->tdes23.tx_rd_des23.first_desc = is_fd;
	p->tdes23.tx_rd_des23.buf1_size = buf1_len;

	p->tdes23.tx_rd_des23.tx_pkt_len.pkt_len.total_pkt_len = pkt_len;

	if (cksum)
		p->tdes23.tx_rd_des23.cksum_ctl = cic_full;
}
