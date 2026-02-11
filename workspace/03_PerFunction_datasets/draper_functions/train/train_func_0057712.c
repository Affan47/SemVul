R3Intersects(const R3Plane& plane, const R3Sphere& sphere)
{

    RNScalar d = R3Distance(plane, sphere.Center());
    if (RNIsGreater(d, sphere.Radius())) return RN_NULL_CLASS_ID;
    else if (RNIsEqual(d, sphere.Radius())) return R3_POINT_CLASS_ID;
    else return RN_UNKNOWN_CLASS_ID;
}
