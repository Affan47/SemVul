MakeScene() {

    VolumeRegion *volumeRegion;
    if (volumeRegions.size() == 0)
        volumeRegion = NULL;
    else if (volumeRegions.size() == 1)
        volumeRegion = volumeRegions[0];
    else
        volumeRegion = new AggregateVolume(volumeRegions);
    Primitive *accelerator = MakeAccelerator(AcceleratorName,
        primitives, AcceleratorParams);
    if (!accelerator)
        accelerator = MakeAccelerator("bvh", primitives, ParamSet());
    if (!accelerator)
        Severe("Unable to create \"bvh\" accelerator.");
    Scene *scene = new Scene(accelerator, lights, volumeRegion);

    primitives.erase(primitives.begin(), primitives.end());
    lights.erase(lights.begin(), lights.end());
    volumeRegions.erase(volumeRegions.begin(), volumeRegions.end());
    return scene;
}
