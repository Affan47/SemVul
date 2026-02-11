GetLocationInfo(const G3D::Vector3& p, const G3D::Vector3& down, float& dist, LocationInfo& info) const
    {
        if (groupModels.empty())
            { return false; }
        WModelAreaCallback callback(groupModels, down);
        groupTree.intersectPoint(p, callback);
        if (callback.hit != groupModels.end())
        {
            info.hitModel = &(*callback.hit);
            dist = callback.zDist;
            return true;
        }
        return false;
    }
