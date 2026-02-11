RangeText(int start, int end) const {
	if (start < end) {
		int len = end - start;
		std::string ret(len, '\0');
		for (int i = 0; i < len; i++) {
			ret[i] = pdoc->CharAt(start + i);
		}
		return ret;
	}
	return std::string();
}
