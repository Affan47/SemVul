getHeight(float x, float y, float z, float maxSearchDist, uint32 phasemask) const
{
    Vector3 v(x, y, z);
    G3D::Ray r(v, Vector3(0, 0, -1));
    DynamicTreeIntersectionCallback callback(phasemask);
    impl.intersectZAllignedRay(r, callback, maxSearchDist);

    if (callback.didHit())
        return v.z - maxSearchDist;
    else
        return -G3D::inf();
}
