simple_action(Packet *p)
{
    const click_ether_vlan *ethh = reinterpret_cast<const click_ether_vlan *>(p->data());
    if (ethh->ether_vlan_proto == htons(ETHERTYPE_8021Q)) {
	SET_VLAN_ANNO(p, ethh->ether_vlan_tci);
	p->pull(sizeof(click_ether_vlan));
    } else if (_has_native_vlan) {
	SET_VLAN_ANNO(p, _native_vlan);
	p->pull(sizeof(click_ether));
    } else {
	checked_output_push(1, p);
	p = 0;
    }
    return p;
}
