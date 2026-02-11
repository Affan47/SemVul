CreateSpotLight(const Transform &l2w, const ParamSet &paramSet) {
    Spectrum I = paramSet.FindOneSpectrum("I", Spectrum(1.0));
    Spectrum sc = paramSet.FindOneSpectrum("scale", Spectrum(1.0));
    float coneangle = paramSet.FindOneFloat("coneangle", 30.);
    float conedelta = paramSet.FindOneFloat("conedeltaangle", 5.);

    Point from = paramSet.FindOnePoint("from", Point(0,0,0));
    Point to = paramSet.FindOnePoint("to", Point(0,0,1));
    Vector dir = Normalize(to - from);
    Vector du, dv;
    CoordinateSystem(dir, &du, &dv);
    Transform dirToZ =
        Transform(Matrix4x4( du.x,  du.y,  du.z, 0.,
                             dv.x,  dv.y,  dv.z, 0.,
                            dir.x, dir.y, dir.z, 0.,
                                0,     0,     0, 1.));
    Transform light2world = l2w *
        Translate(Vector(from.x, from.y, from.z)) * Inverse(dirToZ);
    return new SpotLight(light2world, I * sc, coneangle,
        coneangle-conedelta);
}
