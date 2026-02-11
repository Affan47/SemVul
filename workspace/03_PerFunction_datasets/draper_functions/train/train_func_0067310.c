is_backward(Coord x, Coord y) const {
    if (dimension_ == Dimension_X) {
	return x < thumb_min();
    } else {
	return y < thumb_min();
    }
}
