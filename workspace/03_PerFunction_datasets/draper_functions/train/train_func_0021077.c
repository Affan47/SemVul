addRun(RunNum rn, OctetRole t) {
	std::map< OctetRole,std::vector<RunNum> >::iterator it = runs.find(t);
	if(it != runs.end()) {
		it->second.push_back(rn);
	} else {
		std::vector<RunNum> rns;
		rns.push_back(rn);
		runs.insert(std::make_pair(t,rns));
	}
}
