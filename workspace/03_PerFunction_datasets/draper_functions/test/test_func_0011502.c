GenerateRay(const CameraSample &sample, Ray *ray) const {

    Point Pras(sample.imageX, sample.imageY, 0);
    Point Pcamera;
    RasterToCamera(Pras, &Pcamera);
    *ray = Ray(Pcamera, Vector(0,0,1), 0.f, INFINITY);

    if (lensRadius > 0.) {

        float lensU, lensV;
        ConcentricSampleDisk(sample.lensU, sample.lensV, &lensU, &lensV);
        lensU *= lensRadius;
        lensV *= lensRadius;


        float ft = focalDistance / ray->d.z;
        Point Pfocus = (*ray)(ft);


        ray->o = Point(lensU, lensV, 0.f);
        ray->d = Normalize(Pfocus - ray->o);
    }
    ray->time = Lerp(sample.time, shutterOpen, shutterClose);
    CameraToWorld(*ray, ray);
    return 1.f;
}
