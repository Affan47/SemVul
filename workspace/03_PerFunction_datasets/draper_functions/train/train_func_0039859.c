udp_line(StringAccum &sa, const Packet *p, int transport_length) const
{
    const click_ip *iph = p->ip_header();
    const click_udp *udph = p->udp_header();

    if (transport_length < 4 || !IP_FIRSTFRAG(iph)) {
	address_pair(sa, iph) << (IP_FIRSTFRAG(iph) ? ": truncated-udp" : ": udp");
	return;
    }

    sa << IPAddress(iph->ip_src) << '.' << ntohs(udph->uh_sport) << " > "
       << IPAddress(iph->ip_dst) << '.' << ntohs(udph->uh_dport) << ": ";

    if (transport_length < 8)
	goto truncated_udp;

    sa << "udp " << ntohs(udph->uh_ulen);
    return;

  truncated_udp:
    sa << "truncated-udp";
}
