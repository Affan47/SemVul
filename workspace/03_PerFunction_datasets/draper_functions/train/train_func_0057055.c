shootRay(Ray ray, bool doUnion)
{
    Vector3 intersection;
    Real scale = mVolumeRoot->getChunkParameters()->scale;
    bool intersects = mVolumeRoot->getChunkParameters()->src->getFirstRayIntersection(ray, intersection, scale);
    if (intersects)
    {
        Real radius = (Real)2.5;
        CSGSphereSource sphere(radius, intersection);
        CSGOperationSource *operation = doUnion ? static_cast<CSGOperationSource*>(new CSGUnionSource()) : new CSGDifferenceSource();
        static_cast<TextureSource*>(mVolumeRoot->getChunkParameters()->src)->combineWithSource(operation, &sphere, intersection, radius * (Real)1.5);

        mVolumeRoot->getChunkParameters()->updateFrom = intersection - radius * (Real)1.5;
        mVolumeRoot->getChunkParameters()->updateTo = intersection + radius * (Real)1.5;
        mVolumeRoot->load(mVolumeRootNode, Vector3::ZERO, Vector3(384), 5, mVolumeRoot->getChunkParameters());
        delete operation;
    }
}
