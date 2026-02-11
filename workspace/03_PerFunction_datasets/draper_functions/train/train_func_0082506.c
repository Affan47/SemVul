R3SignedDistance(const R3Plane& plane, const R3Line& line)
{

    if (R3Parallel(plane, line)) {

	return R3SignedDistance(plane, line.Point());
    }
    else {

	return 0.0;
    }
}
