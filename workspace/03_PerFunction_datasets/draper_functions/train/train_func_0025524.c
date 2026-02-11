make_response(u_char tha[6],
                            u_char tpa[4],
                            u_char sha[6],
                            u_char spa[4],
			    Packet *p )
{
    WritablePacket *q = Packet::make(sizeof(click_ether) + sizeof(click_ether_arp));
    if (q == 0) {
	click_chatter("in arp responder: cannot make packet!");
	return 0;
    }


    q->set_device_anno(p->device_anno());

    memset(q->data(), '\0', q->length());

    click_ether *e = (click_ether *) q->data();
    q->set_ether_header(e);
    memcpy(e->ether_dhost, tha, 6);
    memcpy(e->ether_shost, sha, 6);
    e->ether_type = htons(ETHERTYPE_ARP);

    click_ether_arp *ea = (click_ether_arp *) (e + 1);
    ea->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    ea->ea_hdr.ar_pro = htons(ETHERTYPE_IP);
    ea->ea_hdr.ar_hln = 6;
    ea->ea_hdr.ar_pln = 4;
    ea->ea_hdr.ar_op = htons(ARPOP_REPLY);
    memcpy(ea->arp_tha, tha, 6);
    memcpy(ea->arp_tpa, tpa, 4);
    memcpy(ea->arp_sha, sha, 6);
    memcpy(ea->arp_spa, spa, 4);

    return q;
}
