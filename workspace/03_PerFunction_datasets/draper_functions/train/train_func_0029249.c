operator()(const IrradianceSample *sample) {

    float perr = Distance(p, sample->p) / sample->maxDist;
    float nerr = sqrtf((1.f - Dot(n, sample->n)) /
                       (1.f - cosMaxSampleAngleDifference));
    float err = max(perr, nerr);
    PBRT_IRRADIANCE_CACHE_CHECKED_SAMPLE(const_cast<IrradianceSample *>(sample), perr, nerr);
    if (err < 1.) {
        ++nFound;
        float wt = 1.f - err;
        E += wt * sample->E;
        wAvg += wt * sample->wAvg;
        sumWt += wt;
    }
    return true;
}
