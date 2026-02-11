tick() {
	if (!on_) return;

	bool keep=false;
	std::list <toplay>::iterator it;
	for (it=schedule.begin();it!=schedule.end();it++) {
		if ((*it).check()) {
			keep=true;
		}
	}
	if (!keep) schedule.resize(0);

}
