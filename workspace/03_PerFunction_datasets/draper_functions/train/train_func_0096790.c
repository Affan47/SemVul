PointInSelection(Point pt) {
	SelectionPosition pos = SPositionFromLocation(pt);
	int xPos = XFromPosition(pos);
	for (size_t r=0; r<sel.Count(); r++) {
		SelectionRange range = sel.Range(r);
		if (range.Contains(pos)) {
			bool hit = true;
			if (pos == range.Start()) {

				if (pt.x < xPos) {
					hit = false;
				}
			}
			if (pos == range.End()) {

				if (pt.x > xPos) {
					hit = false;
				}
			}
			if (hit)
				return true;
		}
	}
	return false;
}
