simple_action(Packet *p)
{
    click_ether *e = (click_ether *) p->data();
    click_ether_arp *ea = (click_ether_arp *) (e + 1);
    unsigned int tpa;
    memcpy(&tpa, ea->arp_tpa, 4);
    IPAddress ipa = IPAddress(tpa);

    Packet *q = 0;
    if (p->length() >= sizeof(*e) + sizeof(click_ether_arp) &&
	ntohs(e->ether_type) == ETHERTYPE_ARP &&
	ntohs(ea->ea_hdr.ar_hrd) == ARPHRD_ETHER &&
	ntohs(ea->ea_hdr.ar_pro) == ETHERTYPE_IP &&
	ntohs(ea->ea_hdr.ar_op) == ARPOP_REQUEST) {
	EtherAddress ena;
	if (lookup(ipa, ena)) {
	    q = make_response(ea->arp_sha, ea->arp_spa, ena.data(), ea->arp_tpa, p);
	}
    } else {
	struct in_addr ina;
	memcpy(&ina, &ea->arp_tpa, 4);
    }

    p->kill();
    return(q);
}
