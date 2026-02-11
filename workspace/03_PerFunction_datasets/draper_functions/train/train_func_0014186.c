Pdf(const Point &p, const Vector &wi) const {
    Point Pcenter = (*ObjectToWorld)(Point(0,0,0));

    if (DistanceSquared(p, Pcenter) - radius*radius < 1e-4f)
        return Shape::Pdf(p, wi);


    float sinThetaMax2 = radius*radius / DistanceSquared(p, Pcenter);
    float cosThetaMax = sqrtf(max(0.f, 1.f - sinThetaMax2));
    return UniformConePdf(cosThetaMax);
}
