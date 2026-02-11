assign(wsum_t* lhs, wsum_t* rhs) {
	if (type_ == SINGLE_LEVEL_ARITH) { *lhs = *rhs; return; }
	std::memcpy(lhs, rhs, numRules()*sizeof(wsum_t));
	active(lhs) = active(rhs);
}
