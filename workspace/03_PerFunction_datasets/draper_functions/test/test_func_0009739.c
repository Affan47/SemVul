culledBy(
    const Array<Plane>& plane,
	int&				cullingPlane,
	const uint32		_inMask) const {

	uint32 inMask = _inMask;
	assert(plane.size() < 31);


    for (int p = 0; p < plane.size(); ++p) {


		if ((inMask & 1) != 0) {

			bool culled = true;

            int v;


			for (v = 0; (v < 8) && culled; ++v) {
                culled = ! plane[p].halfSpaceContains(corner(v));
			}

			if (culled) {

				cullingPlane = p;

				return true;
            }
		}


		inMask = inMask >> 1;
    }


	cullingPlane = -1;
    return false;
}
