instantiate(match *m) {
	set<term *> n;

	if(m == NULL) {
		if(DEBUG) cout << "prefix::instantiate(NULL): " << to_string() << endl;
		return new prefix(term::u_term++,ctrl,port,suffix->instantiate(m));
	}

	vector<name> nport (port.size());

	for(int i = 0; i<port.size(); i++) {
		nport[i] = m->get_name(port[i]);
		if(DEBUG)
			cout << "prefix::instantiate: nport[" << i << "] = getname(" << port[i] << ") == " << nport[i] << endl;
	}

	if(DEBUG) cout << "prefix::instantiate(!NULL): " << to_string() << endl;

	return new prefix(term::u_term++,ctrl,nport,suffix->instantiate(m));
}
