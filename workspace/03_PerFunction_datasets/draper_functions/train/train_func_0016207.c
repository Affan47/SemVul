fromLines(const char * const *lines) {
	std::vector<std::string> lv;
	while(*lines) {
		lv.push_back(*lines);
		lines++;
	}
	return fromLines(lv);
}
