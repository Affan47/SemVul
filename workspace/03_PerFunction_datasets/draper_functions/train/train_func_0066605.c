dump(std::ofstream& of) const
    {
        of << "Region " << mRegionID << std::endl;
        of << "--------------------------" << std::endl;
        of << "Centre: " << mCentre << std::endl;
        of << "Local AABB: " << mAABB << std::endl;
        of << "Bounding radius: " << mBoundingRadius << std::endl;
        of << "Number of LODs: " << mLodBucketList.size() << std::endl;

        for (LODBucketList::const_iterator i = mLodBucketList.begin();
            i != mLodBucketList.end(); ++i)
        {
            (*i)->dump(of);
        }
        of << "--------------------------" << std::endl;
    }
