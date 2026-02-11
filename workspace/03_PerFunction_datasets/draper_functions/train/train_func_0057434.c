Li(const Scene *scene,
        const Renderer *renderer, const RayDifferential &ray,
        const Intersection &isect, const Sample *sample, RNG &rng, MemoryArena &arena) const {
    Spectrum L(0.f);

    BSDF *bsdf = isect.GetBSDF(ray, arena);
    Vector wo = -ray.d;
    const Point &p = bsdf->dgShading.p;
    const Normal &n = bsdf->dgShading.nn;

    L += isect.Le(wo);


    if (scene->lights.size() > 0) {

        switch (strategy) {
            case SAMPLE_ALL_UNIFORM:
                L += UniformSampleAllLights(scene, renderer, arena, p, n, wo,
                    isect.rayEpsilon, ray.time, bsdf, sample, rng,
                    lightSampleOffsets, bsdfSampleOffsets);
                break;
            case SAMPLE_ONE_UNIFORM:
                L += UniformSampleOneLight(scene, renderer, arena, p, n, wo,
                    isect.rayEpsilon, ray.time, bsdf, sample, rng,
                    lightNumOffset, lightSampleOffsets, bsdfSampleOffsets);
                break;
        }
    }
    if (ray.depth + 1 < maxDepth) {
        Vector wi;

        L += SpecularReflect(ray, bsdf, rng, isect, renderer, scene, sample,
                             arena);
        L += SpecularTransmit(ray, bsdf, rng, isect, renderer, scene, sample,
                              arena);
    }
    return L;
}
