GetFirst(const char *&key, const char *&val) {
	mapss::iterator it = props.begin();
	if (it != props.end()) {
		key = it->first.c_str();
		val = it->second.c_str();
		it++;
		if (it != props.end()) {
			enumnext = it->first;
		} else {
			enumnext = "";
		}
		return true;
	} else {
		return false;
	}
}
