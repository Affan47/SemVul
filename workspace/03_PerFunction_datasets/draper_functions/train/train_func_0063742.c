compare(const LitRep& lhs, const LitRep& rhs) const {
	if (this->operator()(lhs, rhs)) return 1;
	if (this->operator()(rhs, lhs)) return -1;
	return 0;
}
