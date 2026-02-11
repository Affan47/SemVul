print_tcp(struct packet *p, struct iphdr *ip, struct tcphdr *tcp)
{
       fprintf(stdout, "%s [%d] seq=(%u) ack=(%u)\t--->\t%s [%d] len=%d/%d\n",
	       host_lookup(ip->saddr, hl_mode), ntohs(tcp->source),
	       (unsigned int) ntohl(tcp->seq), tcp->ack ? (unsigned int) ntohl(tcp->ack_seq) : 0,
	       host_lookup(ip->daddr, hl_mode), ntohs(tcp->dest), p->p_raw_len, p->p_data_len);
}
