tryFind(const char* key, FindType t) const {
	PrefixRange r = findImpl(key, t);
	if (std::distance(r.first, r.second) == 0 || std::distance(r.first, r.second) > 1) {
		return end();
	}
	return options_.begin() + r.first->second;
}
