GetBox (BoxObj& b) {
    b._left = b._right = _x[0];
    b._bottom = b._top = _y[0];

    for (int i = 1; i < _count; ++i) {
	b._left = min(b._left, _x[i]);
	b._bottom = min(b._bottom, _y[i]);
	b._right = max(b._right, _x[i]);
	b._top = max(b._top, _y[i]);
    }
}
