CRectListContains(const cairo_rectangle_list_t *crcListContainer, const cairo_rectangle_t &crcTest) {
	for (int r=0; r<crcListContainer->num_rectangles; r++) {
		if (CRectContains(crcListContainer->rectangles[r], crcTest))
			return true;
	}
	return false;
}
