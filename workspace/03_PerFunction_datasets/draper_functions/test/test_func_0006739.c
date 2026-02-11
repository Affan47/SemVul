configure(Vector<String> &conf, ErrorHandler *errh)
{
    _v.clear();

    int before = errh->nerrors();
    for (int i = 0; i < conf.size(); i++) {
	IPAddress ipa, mask;
	EtherAddress ena;
	bool have_ena = false;
	int first = _v.size();

	Vector<String> words;
	cp_spacevec(conf[i], words);

	for (int j = 0; j < words.size(); j++)
	    if (cp_ip_address(words[j], &ipa, this))
		add_map(ipa, IPAddress(0xFFFFFFFFU), EtherAddress());
	    else if (cp_ip_prefix(words[j], &ipa, &mask, this))
		add_map(ipa, mask, EtherAddress());
	    else if (cp_ethernet_address(words[j], &ena, this)) {
		if (have_ena)
		    errh->error("argument %d has more than one Ethernet address", i);
		have_ena = true;
	    } else {
		errh->error("argument %d should be `IP/MASK ETHADDR'", i);
		j = words.size();
	    }


	for (int j = 0; !have_ena && j < words.size(); j++)
	    if (cp_ethernet_address(words[j], &ena, this))
		have_ena = true;

	if (first == _v.size())
	    errh->error("argument %d had no IP address and masks", i);
	if (!have_ena)
	    errh->error("argument %d had no Ethernet addresses", i);
	for (int j = first; j < _v.size(); j++)
	    _v[j].ena = ena;
    }

    return (before == errh->nerrors() ? 0 : -1);
}
