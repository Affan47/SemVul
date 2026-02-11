Run() {
    if (!sampler) { progress.Update(); return; }
    MemoryArena arena;
    int sampleCount;
    RNG rng(29 * taskNum);
    int maxSamples = sampler->MaximumSampleCount();
    Sample *samples = origSample->Duplicate(maxSamples);
    while ((sampleCount = sampler->GetMoreSamples(samples, rng)) > 0) {
        for (int i = 0; i < sampleCount; ++i) {
            RayDifferential ray;
            camera->GenerateRayDifferential(samples[i], &ray);
            Intersection isect;
            if (scene->Intersect(ray, &isect))
                (void)irradianceCache->Li(scene, renderer, ray, isect, &samples[i], rng, arena);
        }
        arena.FreeAll();
    }
    delete[] samples;
    delete sampler;
    progress.Update();
}
