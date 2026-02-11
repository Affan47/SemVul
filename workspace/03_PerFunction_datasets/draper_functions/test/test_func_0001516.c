check_syn(struct nes_cm_node *cm_node, struct tcphdr *tcph,
		     struct sk_buff *skb)
{
	int err;

	err = ((ntohl(tcph->ack_seq) == cm_node->tcp_cntxt.loc_seq_num)) ? 0 : 1;
	if (err)
		active_open_err(cm_node, skb, 1);

	return err;
}
