SampleHG(const Vector &w, float g, float u1, float u2) {
    float costheta;
    if (fabsf(g) < 1e-3)
        costheta = 1.f - 2.f * u1;
    else {
        float sqrTerm = (1.f - g * g) /
                        (1.f - g + 2.f * g * u1);
        costheta = (1.f + g * g - sqrTerm * sqrTerm) / (2.f * g);
    }
    float sintheta = sqrtf(max(0.f, 1.f-costheta*costheta));
    float phi = 2.f * M_PI * u2;
    Vector v1, v2;
    CoordinateSystem(w, &v1, &v2);
    return SphericalDirection(sintheta, costheta, phi, v1, v2, w);
}
