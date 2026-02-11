R3Intersects(const R3Line& line, const R3Halfspace& halfspace,
    R3Ray *result)
{

    RNScalar denom = halfspace.Plane().Normal().Dot(line.Vector());


    if (RNIsZero(denom)) {

	if (R3Contains(halfspace, line.Point())) {

	    return R3_LINE_CLASS_ID;
	}
	else {

	    return RN_NULL_CLASS_ID;
	}
    }
    else {

	if (result) {
	    RNScalar t = -(R3SignedDistance(halfspace.Plane(), line.Point())) / denom;
	    R3Point point = line.Point() + line.Vector() * t;
	    R3Vector vector = (RNIsPositive(denom)) ? line.Vector() : -(line.Vector());
	    *result = R3Ray(point, vector);
	}
	return R3_RAY_CLASS_ID;
    }
}
