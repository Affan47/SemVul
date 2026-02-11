reader(Element *e, void *user_data)
{
    EtherPauseSource *eps = static_cast<EtherPauseSource *>(e);
    switch ((intptr_t) user_data) {
    case h_src:
	return EtherAddress(eps->_packet->ether_header()->ether_shost).unparse();
    case h_dst:
	return EtherAddress(eps->_packet->ether_header()->ether_dhost).unparse();
    case h_pausetime: {
	const click_ether_macctl *emc = (const click_ether_macctl *) eps->_packet->network_header();
	return String(ntohs(emc->ether_macctl_param));
    }
    default:
	return String();
    }
}
