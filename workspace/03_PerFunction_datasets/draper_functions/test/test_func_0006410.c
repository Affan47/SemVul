inRange(const uint32_t &ip) {
	for(std::list<rangestruct>::const_iterator i = iprangelist.begin(); i != iprangelist.end(); ++i) {
		if ((ip >= i->startaddr) && (ip <= i->endaddr)) {
			return i->group;
		}
	}
	return -1;
}
