R2Intersects(const R2Ray& ray1, const R2Ray& ray2,
    R2Point *hit_point, RNScalar *hit_t1, RNScalar *hit_t2)
{

    const R2Vector p1 = ray1.Start().Vector();
    const R2Vector p2 = ray2.Start().Vector();
    const R2Vector& v1 = ray1.Vector();
    const R2Vector& v2 = ray2.Vector();
    const R2Vector& n1 = ray1.Normal();
    const R2Vector& n2 = ray2.Normal();
    const RNScalar c1 = ray1.Line().C();
    const RNScalar c2 = ray2.Line().C();


    RNScalar denom = n1.Dot(v2);
    if (RNIsZero(denom)) {

	if (R2Contains(ray1.Line(), ray2.Start())) {

	    if (R2Contains(v1, v2)) {

	        return R2_RAY_CLASS_ID;
	    }
	    else {

	        if (R2Contains(ray1, ray2.Start())) return R2_SPAN_CLASS_ID;
		else return RN_NULL_CLASS_ID;
	    }
	}
	else {

	    return RN_NULL_CLASS_ID;
	}
    }
    else {

        RNScalar t1 = (c2 + n2.Dot(p1)) / denom;
        RNScalar t2 = (c1 + n1.Dot(p2)) / -denom;


	if (RNIsPositiveOrZero(t1) && RNIsPositiveOrZero(t2)) {
	    if (hit_point) *hit_point = ray2.Point(t2);
	    if (hit_t1) *hit_t1 = t1;
	    if (hit_t2) *hit_t2 = t2;
	    return R2_POINT_CLASS_ID;
	}
	else {

	    return RN_NULL_CLASS_ID;
	}
    }
}
