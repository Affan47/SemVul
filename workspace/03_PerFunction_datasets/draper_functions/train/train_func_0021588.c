check_seq(struct nes_cm_node *cm_node, struct tcphdr *tcph,
		     struct sk_buff *skb)
{
	int err = 0;
	u32 seq;
	u32 ack_seq;
	u32 loc_seq_num = cm_node->tcp_cntxt.loc_seq_num;
	u32 rcv_nxt = cm_node->tcp_cntxt.rcv_nxt;
	u32 rcv_wnd;

	seq = ntohl(tcph->seq);
	ack_seq = ntohl(tcph->ack_seq);
	rcv_wnd = cm_node->tcp_cntxt.rcv_wnd;
	if (ack_seq != loc_seq_num)
		err = 1;
	else if (!between(seq, rcv_nxt, (rcv_nxt + rcv_wnd)))
		err = 1;
	if (err) {
		nes_debug(NES_DBG_CM, "%s[%u] create abort for cm_node=%p "
			  "listener=%p state=%d\n", __func__, __LINE__, cm_node,
			  cm_node->listener, cm_node->state);
		indicate_pkt_err(cm_node, skb);
		nes_debug(NES_DBG_CM, "seq ERROR cm_node =%p seq=0x%08X "
			  "rcv_nxt=0x%08X rcv_wnd=0x%x\n", cm_node, seq, rcv_nxt,
			  rcv_wnd);
	}
	return err;
}
