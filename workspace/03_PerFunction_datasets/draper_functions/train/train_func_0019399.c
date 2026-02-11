compute_area(const std::vector<row_crossings_t> &crossings) {
	int64_t area = 0;
	for(size_t y=0; y<crossings.size(); y++) {
		const row_crossings_t &rc = crossings[y];
		size_t nc = rc.size();
		for(size_t cidx=0; cidx<nc/2; cidx++) {
			int from = rc[cidx*2  ];
			int to   = rc[cidx*2+1];
			area += to - from;
		}
	}
	return area;
}
