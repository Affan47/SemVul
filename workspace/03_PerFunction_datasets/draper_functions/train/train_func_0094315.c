Normalize () {
    if (_count != 0) {
        register int i, newcount = 1;
        int lowestLeft, limit = _count;

	if (*_x == _x[_count - 1] && *_y == _y[_count - 1]) {
	    --limit;
	}
	lowestLeft = LowestLeft(_x, _y, limit);
	_normCount = limit + 2;
	_normx = new Coord[_normCount];
	_normy = new Coord[_normCount];

	for (i = lowestLeft; i < limit; ++i, ++newcount) {
	    _normx[newcount] = _x[i];
	    _normy[newcount] = _y[i];
	}
	for (i = 0; i < lowestLeft; ++i, ++newcount) {
	    _normx[newcount] = _x[i];
	    _normy[newcount] = _y[i];
	}

	_normx[newcount] = _normx[1];
	_normy[newcount] = _normy[1];
	--newcount;
	_normx[0] = _normx[newcount];
	_normy[0] = _normy[newcount];
    }
}
