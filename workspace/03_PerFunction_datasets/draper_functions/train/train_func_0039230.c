R2Intersects(const R2Ray& ray, const R2Circle& circle,
    R2Point *hit_point1, R2Vector *hit_normal1, RNScalar *hit_t1)
{

    if (R2Contains(circle, ray.Start())) {
	if (hit_point1) *hit_point1 = ray.Start();
	if (hit_normal1) *hit_normal1 = ray.Vector();
	if (hit_t1) *hit_t1 = 0.0;
	return R2_SPAN_CLASS_ID;
    }
    else {

	R2Vector EO = circle.Center() - ray.Start();
	RNScalar v = EO.Dot(ray.Vector());
	if (RNIsNegativeOrZero(v)) {

	    return RN_NULL_CLASS_ID;
	}
	else {

	    RNScalar disc = circle.Radius() * circle.Radius() - (EO.Dot(EO) - v*v);
	    if (RNIsNegative(disc)) {

		return RN_NULL_CLASS_ID;
	    }
	    else {


		if (hit_t1 || hit_point1 || hit_normal1) {
		    RNScalar d = sqrt(disc);
		    RNScalar t = v - d;
		    if (hit_t1) *hit_t1 = t;
		    if (hit_point1) *hit_point1 = ray.Start() + t * ray.Vector();
		    if (hit_normal1) {
			R2Point p, *pp;
			if (hit_point1) pp = hit_point1;
			else { p = ray.Start() + t * ray.Vector(); pp = &p; }
			*hit_normal1 = (*pp - circle.Centroid()) / circle.Radius();
		    }
		}


		if (RNIsZero(disc)) return R2_POINT_CLASS_ID;
	        else return R2_SPAN_CLASS_ID;
	    }
	}
    }
}
