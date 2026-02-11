interpolate(const Quat& q, Quat r,double t )
{
	Quat res;
    double cosphi;
    double sinphi;
    double phi;
    double scale0, scale1;

    cosphi = q.x * r.x + q.y * r.y + q.z * r.z + q.w * r.w;


    if ( cosphi < 0.0 ) {
	cosphi = -cosphi;
	r.x = -r.x;
	r.y = -r.y;
	r.z = -r.z;
	r.w = -r.w;
    }

    if ( 1.0 - cosphi > EPS ) {

	phi = acos( cosphi );
	sinphi = sin( phi );
	scale0 = sin( phi * ( 1.0 - t ) ) / sinphi;
	scale1 = sin( phi * t ) / sinphi;
    } else {

	scale0 = 1.0 - t;
	scale1 = t;
    }

    res.x = scale0 * q.x + scale1 * r.x;
    res.y = scale0 * q.y + scale1 * r.y;
    res.z = scale0 * q.z + scale1 * r.z;
    res.w = scale0 * q.w + scale1 * r.w;

    return res;
}
