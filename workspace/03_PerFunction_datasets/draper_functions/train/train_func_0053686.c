problemComplexity() const {
	uint32 r = numBinary() + numTernary();
	for (uint32 i = 0; i != master()->constraints_.size(); ++i) {
		r += master()->constraints_[i]->estimateComplexity(*master());
	}
	return r;
}
