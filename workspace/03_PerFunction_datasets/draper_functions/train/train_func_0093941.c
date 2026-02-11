CreateProjectionLight(const Transform &light2world,
        const ParamSet &paramSet) {
    Spectrum I = paramSet.FindOneSpectrum("I", Spectrum(1.0));
    Spectrum sc = paramSet.FindOneSpectrum("scale", Spectrum(1.0));
    float fov = paramSet.FindOneFloat("fov", 45.);
    string texname = paramSet.FindOneFilename("mapname", "");
    return new ProjectionLight(light2world, I * sc, texname, fov);
}
