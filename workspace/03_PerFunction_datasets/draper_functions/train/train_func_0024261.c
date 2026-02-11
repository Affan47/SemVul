MakeVolumeIntegrator(const string &name,
        const ParamSet &paramSet) {
    VolumeIntegrator *vi = NULL;
    if (name == "single")
        vi = CreateSingleScatteringIntegrator(paramSet);
    else if (name == "emission")
        vi = CreateEmissionVolumeIntegrator(paramSet);
    else
        Warning("Volume integrator \"%s\" unknown.", name.c_str());
    paramSet.ReportUnused();
    return vi;
}
