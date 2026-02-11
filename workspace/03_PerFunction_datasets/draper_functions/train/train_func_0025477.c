share_literals(const Clause& c) const {
	for (Clause::const_iterator itr = c.cbegin(); itr != c.cend(); itr++) {
		if (contain(*itr))
			return true;
	}
	return false;
}
