initiate_new_session(struct lro *lro, u8 *l2h,
				 struct iphdr *ip, struct tcphdr *tcp,
				 u32 tcp_pyld_len, u16 vlan_tag)
{
	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);
	lro->l2h = l2h;
	lro->iph = ip;
	lro->tcph = tcp;
	lro->tcp_next_seq = tcp_pyld_len + ntohl(tcp->seq);
	lro->tcp_ack = tcp->ack_seq;
	lro->sg_num = 1;
	lro->total_len = ntohs(ip->tot_len);
	lro->frags_len = 0;
	lro->vlan_tag = vlan_tag;


	if (tcp->doff == 8) {
		__be32 *ptr;
		ptr = (__be32 *)(tcp+1);
		lro->saw_ts = 1;
		lro->cur_tsval = ntohl(*(ptr+1));
		lro->cur_tsecr = *(ptr+2);
	}
	lro->in_use = 1;
}
