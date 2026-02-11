Turbulence(const Point &P, const Vector &dpdx, const Vector &dpdy,
                 float omega, int maxOctaves) {

    float s2 = max(dpdx.LengthSquared(), dpdy.LengthSquared());
    float foctaves = min((float)maxOctaves, 1.f - .5f * Log2(s2));
    int octaves = Floor2Int(foctaves);


    float sum = 0., lambda = 1., o = 1.;
    for (int i = 0; i < octaves; ++i) {
        sum += o * fabsf(Noise(lambda * P));
        lambda *= 1.99f;
        o *= omega;
    }
    float partialOctave = foctaves - octaves;
    sum += o * SmoothStep(.3f, .7f, partialOctave) *
           fabsf(Noise(lambda * P));


    sum += (maxOctaves - foctaves) * 0.2f;

    return sum;
}
