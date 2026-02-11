push(int, Packet *p)
{
#define EXCHANGE(a,b,t) { t = a; a = b; b = t; }
    IPAddress a = p->dst_ip_anno();
    int ei = -1;

    if (a && a == _last_addr)
	ei = _last_entry;
#ifdef IP_RT_CACHE2
    else if (a && a == _last_addr2)
	ei = _last_entry2;
#endif
    else if ((ei = lookup_entry(a)) >= 0) {
#ifdef IP_RT_CACHE2
	_last_addr2 = _last_addr;
	_last_entry2 = _last_entry;
#endif
	_last_addr = a;
	_last_entry = ei;
    } else {
	static int complained = 0;
	if (++complained <= 5)
	    click_chatter("LinearIPLookup: no route for %s", a.unparse().c_str());
	p->kill();
	return;
    }

    const IPRoute &e = _t[ei];
    if (e.gw)
	p->set_dst_ip_anno(e.gw);
    output(e.port).push(p);
}
