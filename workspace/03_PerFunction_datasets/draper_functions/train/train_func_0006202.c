InSelectionForEOL(int pos) const {
	for (size_t i=0; i<ranges.size(); i++) {
		if (!ranges[i].Empty() && (pos > ranges[i].Start().Position()) && (pos <= ranges[i].End().Position()))
			return i == mainRange ? 1 : 2;
	}
	return 0;
}
