PathL(const MLTSample &sample,
        const Scene *scene, MemoryArena &arena, const Camera *camera,
        const Distribution1D *lightDistribution,
        PathVertex *cameraPath, PathVertex *lightPath,
        RNG &rng) const {

    PBRT_STARTED_GENERATING_CAMERA_RAY((CameraSample *)(&sample.cameraSample));
    RayDifferential cameraRay;
    float cameraWt = camera->GenerateRayDifferential(sample.cameraSample,
                                                     &cameraRay);
    cameraRay.ScaleDifferentials(1.f / sqrtf(nPixelSamples));
    PBRT_FINISHED_GENERATING_CAMERA_RAY((CameraSample *)(&sample.cameraSample), &cameraRay, cameraWt);
    RayDifferential escapedRay;
    Spectrum escapedAlpha;
    uint32_t cameraLength = GeneratePath(cameraRay, cameraWt, scene, arena,
        sample.cameraPathSamples, cameraPath, &escapedRay, &escapedAlpha);
    if (!bidirectional) {

        return Lpath(scene, cameraPath, cameraLength, arena,
                     sample.lightingSamples, rng, sample.cameraSample.time,
                     lightDistribution, escapedRay, escapedAlpha);
    }
    else {


        PBRT_MLT_STARTED_SAMPLE_LIGHT_FOR_BIDIR();
        float lightPdf, lightRayPdf;
        uint32_t lightNum = lightDistribution->SampleDiscrete(sample.lightNumSample,
                                                              &lightPdf);
        const Light *light = scene->lights[lightNum];
        Ray lightRay;
        Normal Nl;
        LightSample lrs(sample.lightRaySamples[0], sample.lightRaySamples[1],
                        sample.lightRaySamples[2]);
        Spectrum lightWt = light->Sample_L(scene, lrs, sample.lightRaySamples[3],
            sample.lightRaySamples[4], sample.cameraSample.time, &lightRay,
            &Nl, &lightRayPdf);
        PBRT_MLT_FINISHED_SAMPLE_LIGHT_FOR_BIDIR();
        if (lightWt.IsBlack() || lightRayPdf == 0.f) {

            return Lpath(scene, cameraPath, cameraLength, arena,
                         sample.lightingSamples, rng, sample.cameraSample.time,
                         lightDistribution, escapedRay, escapedAlpha);
        }
        else {

            lightWt *= AbsDot(Normalize(Nl), lightRay.d) / (lightPdf * lightRayPdf);
            uint32_t lightLength = GeneratePath(RayDifferential(lightRay), lightWt,
                scene, arena, sample.lightPathSamples, lightPath, NULL, NULL);

            return Lbidir(scene, cameraPath, cameraLength, lightPath, lightLength,
                arena, sample.lightingSamples, rng, sample.cameraSample.time,
                lightDistribution, escapedRay, escapedAlpha);
        }
    }
}
