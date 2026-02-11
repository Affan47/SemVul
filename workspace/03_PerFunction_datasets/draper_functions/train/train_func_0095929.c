R3Intersects(const R3Plane& plane, const R3Box& box)
{

    RNOctant octant = plane.Normal().Octant();
    if (R3SignedDistance(plane, box.Corner(octant)) < 0) return RN_NULL_CLASS_ID;
    if (R3SignedDistance(plane, box.Corner(~octant & 0x7)) > 0) return RN_NULL_CLASS_ID;
    return RN_UNKNOWN_CLASS_ID;
}
