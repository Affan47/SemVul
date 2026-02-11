Sample(float u1, float u2, Normal *Ns) const {
    Point p;
    ConcentricSampleDisk(u1, u2, &p.x, &p.y);
    p.x *= radius;
    p.y *= radius;
    p.z = height;
    *Ns = Normalize((*ObjectToWorld)(Normal(0,0,1)));
    if (ReverseOrientation) *Ns *= -1.f;
    return (*ObjectToWorld)(p);
}
