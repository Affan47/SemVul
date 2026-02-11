contain(int l) const {
	if (clause.size() <= 0)
		return false;
	return (std::binary_search(clause.begin(), clause.end(), l));
}
