randomizedQsort( std::vector< SORT_TYPE> &vec, size_t p, size_t r) {
	if ( p < r && r < vec.size()) {
		const size_t q = randomizedPartation( vec, p, r);

		randomizedQsort( vec, p, q - 1);
		randomizedQsort( vec, q + 1, r);
	}
}
