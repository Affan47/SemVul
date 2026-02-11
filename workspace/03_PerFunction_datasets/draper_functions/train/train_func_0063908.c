toLower(const std::string& s) {
	std::string ret; ret.reserve(s.size());
	std::transform(s.begin(), s.end(), std::back_inserter(ret), ToLower());
	return ret;
}
