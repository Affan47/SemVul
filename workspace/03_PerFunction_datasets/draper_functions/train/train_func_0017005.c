print_components() {
	if (ClauseSet::UPPER_WMC) {
		for (ClauseComponentMap::const_iterator itr = clause_components.cbegin(); itr != clause_components.cend(); itr++) {
			cout<<itr->first<<": "<<itr->second<<endl;
		}
	}
}
