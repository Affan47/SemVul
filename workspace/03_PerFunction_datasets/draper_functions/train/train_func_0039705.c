Intersect(const Ray &r, float *tHit, float *rayEpsilon,
                     DifferentialGeometry *dg) const {

    Ray ray;
    (*WorldToObject)(r, &ray);


    if (fabsf(ray.d.z) < 1e-7) return false;
    float thit = (height - ray.o.z) / ray.d.z;
    if (thit < ray.mint || thit > ray.maxt)
        return false;


    Point phit = ray(thit);
    float dist2 = phit.x * phit.x + phit.y * phit.y;
    if (dist2 > radius * radius || dist2 < innerRadius * innerRadius)
        return false;


    float phi = atan2f(phit.y, phit.x);
    if (phi < 0) phi += 2. * M_PI;
    if (phi > phiMax)
        return false;


    float u = phi / phiMax;
    float oneMinusV = ((sqrtf(dist2)-innerRadius) /
                       (radius-innerRadius));
    float invOneMinusV = (oneMinusV > 0.f) ? (1.f / oneMinusV) : 0.f;
    float v = 1.f - oneMinusV;
    Vector dpdu(-phiMax * phit.y, phiMax * phit.x, 0.);
    Vector dpdv(-phit.x * invOneMinusV, -phit.y * invOneMinusV, 0.);
    dpdu *= phiMax * INV_TWOPI;
    dpdv *= (radius - innerRadius) / radius;
    Normal dndu(0,0,0), dndv(0,0,0);


    const Transform &o2w = *ObjectToWorld;
    *dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv),
                               o2w(dndu), o2w(dndv), u, v, this);


    *tHit = thit;


    *rayEpsilon = 5e-4f * *tHit;
    return true;
}
