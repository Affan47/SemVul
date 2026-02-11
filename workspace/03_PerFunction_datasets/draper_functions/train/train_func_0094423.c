dump() const
{
    StringAccum sa;
    for (uint32_t i = 0; i < PREF_HASHSIZE; i++)
	for (int rt_i = _rt_hashtbl[i]; rt_i >= 0; rt_i = _rtable[rt_i].ll_next) {
	    const CleartextEntry &rt = _rtable[rt_i];
	    if (_vport[rt.vport].port != -1) {
		IPRoute route = IPRoute(IPAddress(htonl(rt.prefix)), IPAddress::make_prefix(rt.plen), _vport[rt.vport].gw, _vport[rt.vport].port);
		route.unparse(sa, true) << '\n';
	    }
	}
    return sa.take_string();
}
