IntersectRay(const G3D::Ray& ray, float& distance, bool stopAtFirstHit) const
    {


        if (groupModels.size() == 1)
            return groupModels[0].IntersectRay(ray, distance, stopAtFirstHit);

        WModelRayCallBack isc(groupModels);
        groupTree.intersectRay(ray, isc, distance, stopAtFirstHit);
        return isc.hit;
    }
