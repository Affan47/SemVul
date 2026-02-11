Pdf(const Point &p, const Vector &wi) const {
    float pdf = 0.f;
    for (uint32_t i = 0; i < shapes.size(); ++i)
        pdf += areas[i] * shapes[i]->Pdf(p, wi);
    return pdf / sumArea;
}
