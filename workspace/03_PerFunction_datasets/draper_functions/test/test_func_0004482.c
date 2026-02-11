conn_update_table(struct packet *p, struct ethhdr *ethh, struct iphdr *iph)
{
	struct tcphdr *tcph = p->p_hdr.p_tcph;

	if (tcph->syn && !tcph->ack) {
		if (conn_add_policy(iph, tcph)) {
			conn_add(p);
		}
	} else if (tcph->rst || tcph->fin) {
		#if 0
		if (conn_add_policy(iph, tcph))
		#endif
			conn_del(p);
	} else {
		#if 0
		if (conn_add_policy(iph, tcph))
		#endif
			conn_add_update(p);
	}
}
