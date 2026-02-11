handle_ack_pkt(struct nes_cm_node *cm_node, struct sk_buff *skb,
			  struct tcphdr *tcph)
{
	int datasize = 0;
	u32 inc_sequence;
	int ret = 0;
	int optionsize;

	optionsize = (tcph->doff << 2) - sizeof(struct tcphdr);

	if (check_seq(cm_node, tcph, skb))
		return -EINVAL;

	skb_pull(skb, tcph->doff << 2);
	inc_sequence = ntohl(tcph->seq);
	datasize = skb->len;
	switch (cm_node->state) {
	case NES_CM_STATE_SYN_RCVD:

		cleanup_retrans_entry(cm_node);
		ret = handle_tcp_options(cm_node, tcph, skb, optionsize, 1);
		if (ret)
			break;
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		cm_node->state = NES_CM_STATE_ESTABLISHED;
		if (datasize) {
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			nes_get_remote_addr(cm_node);
			handle_rcv_mpa(cm_node, skb);
		} else {
			dev_kfree_skb_any(skb);
		}
		break;
	case NES_CM_STATE_ESTABLISHED:

		cleanup_retrans_entry(cm_node);
		if (datasize) {
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			handle_rcv_mpa(cm_node, skb);
		} else {
			drop_packet(skb);
		}
		break;
	case NES_CM_STATE_MPAREQ_SENT:
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		if (datasize) {
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			handle_rcv_mpa(cm_node, skb);
		} else {
			dev_kfree_skb_any(skb);
		}
		break;
	case NES_CM_STATE_LISTENING:
		cleanup_retrans_entry(cm_node);
		cm_node->state = NES_CM_STATE_CLOSED;
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_CLOSED:
		cleanup_retrans_entry(cm_node);
		add_ref_cm_node(cm_node);
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_LAST_ACK:
	case NES_CM_STATE_CLOSING:
		cleanup_retrans_entry(cm_node);
		cm_node->state = NES_CM_STATE_CLOSED;
		cm_node->cm_id->rem_ref(cm_node->cm_id);
		rem_ref_cm_node(cm_node->cm_core, cm_node);
		drop_packet(skb);
		break;
	case NES_CM_STATE_FIN_WAIT1:
		cleanup_retrans_entry(cm_node);
		drop_packet(skb);
		cm_node->state = NES_CM_STATE_FIN_WAIT2;
		break;
	case NES_CM_STATE_SYN_SENT:
	case NES_CM_STATE_FIN_WAIT2:
	case NES_CM_STATE_TSA:
	case NES_CM_STATE_MPAREQ_RCVD:
	case NES_CM_STATE_UNKNOWN:
	default:
		cleanup_retrans_entry(cm_node);
		drop_packet(skb);
		break;
	}
	return ret;
}
