CRectContains(const cairo_rectangle_t &crcContainer, const cairo_rectangle_t &crcTest) {
	return
		(crcTest.x >= crcContainer.x) && ((crcTest.x + crcTest.width) <= (crcContainer.x + crcContainer.width)) &&
		(crcTest.y >= crcContainer.y) && ((crcTest.y + crcTest.height) <= (crcContainer.y + crcContainer.height));
}
